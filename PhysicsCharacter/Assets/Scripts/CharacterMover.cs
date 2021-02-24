using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterMover : MonoBehaviour
{
    public float speed = 10;
    public float jumpForce = 10;
    public bool isGrounded;
    private bool jumpInput = false;

    CharacterController cc;
    
    Transform cam;
    Vector2 moveInput = new Vector2();
    public Vector3 velocity = new Vector3();

    // Update is called once per frame
    void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        jumpInput = Input.GetButton("Jump");
    }

    // Start is called before the first frame update
    void Start()
    {
        cc = GetComponent<CharacterController>();
        cam = Camera.main.transform;
    }

    void FixedUpdate()
    {
        Vector3 delta;

        // find the horizontal unit vector facing forward from the camera
        Vector3 camForward = cam.forward;
        camForward.y = 0;
        camForward.Normalize();

        // use our camera's right vector, which is always horizontal
        Vector3 camRight = cam.right;
        delta = (moveInput.x * camRight + moveInput.y * camForward) * speed * Time.fixedDeltaTime;

        if (isGrounded || moveInput.x != 0 || moveInput.y != 0)
        {
            velocity.x = delta.x;
            velocity.z = delta.z;
        }

        // check for jumping
        if (jumpInput && isGrounded)
        {
            velocity.y = jumpForce;
        }

        if (isGrounded && velocity.y < 0)
        {
            velocity.y = 0;
        }

        // apply gravity after zeroing velocity so we register as grounded still
        velocity += Physics.gravity * Time.fixedDeltaTime;

        // and apply this to our positional update this frame
        //delta += velocity * Time.deltaTime;

        cc.Move(velocity * Time.deltaTime);
        isGrounded = cc.isGrounded;

        transform.forward = camForward;

    }
}
