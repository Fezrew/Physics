using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterMover : MonoBehaviour
{
    public float speed = 10;
    public float jumpForce = 10;
    public float launchForce = 1;
    public float throwRange = 10;
    public float throwForce = 1;
    float groundDist = 0.1f;
    public bool isGrounded;
    private bool jumpInput = false;

    CharacterController cc;

    Animator animator;
    Transform cam;
    Ragdoll ragdoll;
    Vector2 moveInput = new Vector2();
    public LayerMask Player;
    public Vector3 velocity = new Vector3();

    // Start is called before the first frame update
    void Start()
    {
        cc = GetComponent<CharacterController>();
        cam = Camera.main.transform;
        animator = GetComponentInChildren<Animator>();
        ragdoll = GetComponent<Ragdoll>();
    }

    // Update is called once per frame
    void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        jumpInput = Input.GetButton("Jump");
        float move = 0;

        if (moveInput.x > 0)
        {
            move += moveInput.x;
        }
        if (moveInput.x < 0)
        {
            move -= moveInput.x;
        }
        if (moveInput.y > 0)
        {
            move += moveInput.y;
        }
        if (moveInput.y < 0)
        {
            move -= moveInput.y;
        }
        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            //When you mouse click, throw the player into a ragdoll in the opposite direction of the camera's forward
            if (ragdoll != null && !ragdoll.RagdollOn)
            {
                ragdoll.RagdollOn = true;
                ragdoll.hips.AddForce(new Vector3(cam.forward.x * -launchForce, cam.forward.y * -launchForce, cam.forward.z * -launchForce));
                //velocity = new Vector3(cam.forward.x * -yeetForce, cam.forward.y * -yeetForce, cam.forward.z * -yeetForce);
            }
        }
        if (Input.GetKeyDown(KeyCode.Mouse1))
        {
            RaycastHit hit;
            if (Physics.Raycast(cam.position, cam.forward, out hit, throwRange, ~Player))
            {
                if (hit.collider.GetComponent<Rigidbody>())
                {
                    Rigidbody rb;
                    rb = hit.collider.GetComponent<Rigidbody>();

                    rb.AddForce(new Vector3(cam.forward.x * throwForce, cam.forward.y * -launchForce, cam.forward.z * throwForce));
                    Debug.Log("Collided with: " );
                }
            }
        }

        animator.SetFloat("Forwards", move);
        animator.SetBool("Jump", !isGrounded);

        if (!cc.enabled)
        {
            velocity = new Vector3(0, 0, 0);
        }
    }

    void FixedUpdate()
    {
        if (animator.enabled)
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
                //Rotate the model to match the cameras forward
                transform.forward = camForward;

                //Rotate the model to face a direction relative to the direction of movement
                //transform.forward = new Vector3(velocity.x, transform.forward.y, velocity.z);
            }
        }
    }

    public Vector3 hitDirection;
    void OnControllerColliderHit(ControllerColliderHit hit)
    {
        hitDirection = hit.point - transform.position;
    }

}
