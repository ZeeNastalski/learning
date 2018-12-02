using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using UnityEditor.Experimental.UIElements;
using UnityEngine;
using UnityEngine.Analytics;

public class CalculatePivot : MonoBehaviour
{

    private List<Tuple<Vector3, Quaternion>> samples = new List<Tuple<Vector3, Quaternion>>();

    public string SamplesFile = @"c:\temp\samples.csv";
    public bool RecordingSamples = false;

    public int SamplesCnt;

    public float Back = 0.1675003f;

    public float Down = 0.2256003f;

    public float Error;

    public float BestBack;
    public float BestDown;
    public float BestError;


    // tracking monitor section
    public float InactivityRangeThreshold = 0.04f;
    public int InactivityTimeThresholdMs = 2000;
    
    private List<Vector3> pivotPositionSamples = new List<Vector3>();
    public bool isTrackingOk = false;
    private DateTime lastCheckTime = DateTime.Now;


    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

	    if (Input.GetKeyDown(KeyCode.Space))
        {
            //start recording
            RecordingSamples = !RecordingSamples;
        }

	    if (Input.GetKeyDown(KeyCode.C))
	    {
	        CalculateNewPivot();
	    }

	    if (Input.GetKeyDown(KeyCode.S))
	    {
	        SaveSamples();
	    }

	    if (Input.GetKeyDown(KeyCode.L))
	    {
	        LoadSamples();
	    }

        if (RecordingSamples)
	    {
            if(Time.frameCount % 10 == 0)
	        { 
                // record sample every 10th frame
	            var tp = Tuple.Create(transform.position, transform.rotation);
	            samples.Add(tp);
	            SamplesCnt++;
	        }
	    }

	    UpdateTrackingStatus();

	}

    private void UpdateTrackingStatus()
    {
        if ((DateTime.Now - lastCheckTime).TotalMilliseconds > InactivityTimeThresholdMs)
        {
            Vector3 span = BoundingBoxSpan(pivotPositionSamples);
            
        


            Debug.Log(
                $"{span.x:0.00000}, {span.y:0.00000}, {span.z:0.00000} - {span.magnitude:0.00000} ({pivotPositionSamples.Count})");

            if (span.magnitude > InactivityRangeThreshold)
            {
                NotifyTrackingAcquired();
            }
            else
            {
                NotifyTrackingLost();
            }

            pivotPositionSamples.Clear();
            lastCheckTime = DateTime.Now;
        }
        else
        {
            Vector3 point = transform.position + Back * (transform.rotation * Vector3.back) +
                                                 Down * (transform.rotation * Vector3.down);

            pivotPositionSamples.Add(point);
        }
    }

    private void NotifyTrackingAcquired()
    {
        if (!isTrackingOk)
        {
            Debug.Log("Tracking Acquired");
            isTrackingOk = true;
        }
    }

    private void NotifyTrackingLost()
    {
        if (isTrackingOk)
        {
            Debug.Log("Tracking Lost");
            isTrackingOk = false;
        }
    }

    private Vector3 BoundingBoxSpan(List<Vector3> points)
    {
        
        if(points.Count == 0)
            return Vector3.zero;
        
        Vector3 max;
        max.x = Single.MinValue;
        max.y = Single.MinValue;
        max.z = Single.MinValue;

        Vector3 min;
        min.x = Single.MaxValue;
        min.y = Single.MaxValue;
        min.z = Single.MaxValue;

        foreach (var point in points)
        {
            max.x = (point.x > max.x) ? point.x : max.x;
            max.y = (point.y > max.y) ? point.y : max.y;
            max.z = (point.z > max.z) ? point.z : max.z;

            min.x = (point.x < min.x) ? point.x : min.x;
            min.y = (point.y < min.y) ? point.y : min.y;
            min.z = (point.z < min.z) ? point.z : min.z;
        }

        return max - min;
    }
    private void SaveSamples()
    {
        List<string> lines = new List<string>();

        foreach (var sample in samples)
        {
            string[] line = new string[7];
            line[0] = sample.Item1.x.ToString();
            line[1] = sample.Item1.y.ToString();
            line[2] = sample.Item1.z.ToString();

            line[3] = sample.Item2.x.ToString();
            line[4] = sample.Item2.y.ToString();
            line[5] = sample.Item2.z.ToString();
            line[6] = sample.Item2.w.ToString();

            lines.Add( String.Join(",", line));                            
        }

        File.WriteAllLines(SamplesFile, lines);
    }

    private void LoadSamples()
    {
        string[] lines = File.ReadAllLines(SamplesFile);

        samples.Clear();
        foreach (var lineStr in lines)
        {
            string[] line = lineStr.Split(',');

            Vector3 pos;
            pos.x = float.Parse(line[0]);
            pos.y = float.Parse(line[1]);
            pos.z = float.Parse(line[2]);

            Quaternion rot;
            rot.x = float.Parse(line[3]);
            rot.y = float.Parse(line[4]);
            rot.z = float.Parse(line[5]);
            rot.w = float.Parse(line[6]);

            samples.Add(Tuple.Create(pos,rot));
        }

        SamplesCnt = samples.Count;
    }

    private void CalculateNewPivot()
    {
        Error = CalculateError(Back, Down);

        BestError = Single.MaxValue; ;

        float backStart = 0.13f;
        float backEnd = 0.20f;
        float downStart = 0.15f;
        float downEnd = 0.30f;
        float step = 0.0002f;

        float back = backStart;
        float down = downStart;

        while (back < backEnd)
        {
            down = downStart;
            while (down < downEnd)
            {
                float newError = CalculateError(back, down);

                if (newError < BestError)
                {
                    BestError = newError;
                    BestBack = back;
                    BestDown = down;
                }
                
                down += step;
            }
            back += step;
        }       
    }



    private float CalculateError(float back, float down)
    {
        Vector3 max;
        max.x = Single.MinValue;
        max.y = Single.MinValue;
        max.z = Single.MinValue;

        Vector3 min;
        min.x = Single.MaxValue;
        min.y = Single.MaxValue;
        min.z = Single.MaxValue;


        foreach (var sample in samples)
        {
            Vector3 pos = sample.Item1;
            Quaternion rot = sample.Item2;

            Vector3 point = pos + back * (rot * Vector3.back) + down * (rot * Vector3.down);

            max.x = (point.x > max.x) ? point.x : max.x;
            max.y = (point.y > max.y) ? point.y : max.y;
            max.z = (point.z > max.z) ? point.z : max.z;

            min.x = (point.x < min.x) ? point.x : min.x;
            min.y = (point.y < min.y) ? point.y : min.y;
            min.z = (point.z < min.z) ? point.z : min.z;
        }

        return Vector3.Distance(min, max);
    }

}
