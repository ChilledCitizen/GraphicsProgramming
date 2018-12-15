using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementController : MonoBehaviour
{

    // Transforms to act as start and end markers for the journey.
    public Transform startMarker;
    public Transform endMarker;

    // Movement speed in units/sec.
    public float speed = 1.0F;

    // Time when the movement started.
    private float startTime;

    // Total distance between the markers.
    private float journeyLength;
    private bool goingToEnd = true;

    void Start()
    {
        
    }

    // Follows the target position like with a spring
    void Update()
    {
        
        // Set our position as a fraction of the distance between the markers.
        if (goingToEnd)
        {
            transform.position = Vector3.Lerp(startMarker.position, endMarker.position, speed);
            if (transform.position == endMarker.position)
            {
                goingToEnd = false;
            }

        }

        if (!goingToEnd)
        {
            transform.position = Vector3.Lerp(endMarker.position, startMarker.position, speed);
            if (transform.position == startMarker.position)
            {
                goingToEnd = true;
            }
        }

    }
}
