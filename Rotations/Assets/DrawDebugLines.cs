using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawDebugLines : MonoBehaviour
{
    public Color color = Color.green;
    public float linger = 1000;

    private Vector3 lastPosition;

    
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

	    if (Time.frameCount < 30)
	    {
	        lastPosition = transform.position;
            return;
	    }

	    Debug.DrawLine(lastPosition, transform.position, color, linger);
	    lastPosition = transform.position;
	}
}
