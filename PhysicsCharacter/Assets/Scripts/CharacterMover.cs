using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterMover : MonoBehaviour
{
    public float speed = 10;
    public float jumpForce = 10;
    float groundDist = 0.1f;
    public bool isGrounded;
    private bool jumpInput = false;

    CharacterController cc;

    Animator animator;
    Transform cam;
    Vector2 moveInput = new Vector2();
    public Vector3 velocity = new Vector3();

    // Start is called before the first frame update
    void Start()
    {
        cc = GetComponent<CharacterController>();
        cam = Camera.main.transform;
        animator = GetComponentInChildren<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        jumpInput = Input.GetButton("Jump");

        animator.SetFloat("Forwards", moveInput.y);
        animator.SetBool("Jump", !isGrounded);
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

        if (!isGrounded)
        {
            hitDirection = Vector3.zero;
        }

        // slide objects off surfaces they're hanging on to
        if (moveInput.x == 0 && moveInput.y == 0)
        {
            Vector3 horizontalHitDirection = hitDirection;
            horizontalHitDirection.y = 0;
            float displacement = horizontalHitDirection.magnitude;

            if (displacement > 0)
            {
                RaycastHit hit;
                if (!Physics.Raycast(transform.position, Vector3.down, out hit, groundDist))
                {
                    velocity -= 0.2f * horizontalHitDirection / displacement;
                }
            }
        }

        cc.Move(velocity * Time.deltaTime);
        isGrounded = cc.isGrounded;

        if (moveInput.x != 0 || moveInput.y != 0)
        {
            transform.forward = camForward;
            //transform.forward = new Vector3(camForward.x * moveInput.x, camForward.y , camForward.z * moveInput.y);
        }
    }

    public Vector3 hitDirection;
    void OnControllerColliderHit(ControllerColliderHit hit)
    {
        hitDirection = hit.point - transform.position;
    }

}
