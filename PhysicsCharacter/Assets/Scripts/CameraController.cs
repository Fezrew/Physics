using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public Transform target;
    float heightOffset = 0.75f;
    public float rotateSpeed = 50;
    public float distance = 5;
    float currentDistance;
    public float relaxSpeed;
    public bool invertY;

    Vector3 GetTargetPosition()
    {
        return target.position + heightOffset * Vector3.up;
    }

    // Start is called before the first frame update
    void Start()
    {
        currentDistance = distance;
        Cursor.lockState = CursorLockMode.Locked;
    }

    // Update is called once per frame
    void Update()
    {

        Vector3 angles = transform.eulerAngles;

        float dx;
        float dy = Input.GetAxis("Mouse X");
        if (invertY)
        {
            dx = Input.GetAxis("Mouse Y");
        }
        else
        {
            dx = -Input.GetAxis("Mouse Y");
        }

        // look up and down by rotating around X-axis
        angles.x = Mathf.Clamp(angles.x + dx * rotateSpeed * Time.deltaTime, 0, 70);
        // spin the camera round
        angles.y += dy * rotateSpeed * Time.deltaTime;
        transform.eulerAngles = angles;

        RaycastHit hit;
        if (Physics.Raycast(GetTargetPosition(), -transform.forward, out hit, distance))
        {
            if (!hit.collider.CompareTag("Player"))
            {
                // snap the camera right in to where the collision happened
                currentDistance = hit.distance;
            }
        }
        else
        {
            // relax the camera back to the desired distance
            currentDistance = Mathf.MoveTowards(currentDistance, distance, Time.deltaTime * relaxSpeed);
        }

        // look at the target point
        transform.position = GetTargetPosition() - currentDistance * transform.forward;
    }
}
