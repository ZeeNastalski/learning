using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Looksy : MonoBehaviour
{
    public float rotationSpeed = 30f;

    public GameObject Point;
    public float back = 1.0f;
    public float down = 1.0f;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update ()
	{

	    float v = Input.GetAxis("Vertical");
	    float h = Input.GetAxis("Horizontal");
	    float r = Input.GetAxis("Roll");

        // roll
        transform.rotation *= Quaternion.Euler( 0, 0, r*rotationSpeed*Time.deltaTime);

        // pitch
	    transform.rotation *= Quaternion.Euler(v * rotationSpeed * Time.deltaTime, 0, 0);

        // yaw
	    transform.rotation *= Quaternion.Euler(0, h * rotationSpeed * Time.deltaTime, 0);

	    Vector3 pointPosition = transform.position + back * (transform.rotation * Vector3.back) + down * (transform.rotation * Vector3.down);

	    Point.transform.position = pointPosition;

	}
}
