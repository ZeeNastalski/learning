using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowPivot : MonoBehaviour
{

    public GameObject Pivot;
    public float Back = 0.167f;
    public float Down = 0.220f;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
	    	Pivot.transform.position = transform.position + Back * (transform.rotation * Vector3.back) + 
	    	                                                Down * (transform.rotation * Vector3.down);
    }
}
