using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Ragdoll : MonoBehaviour
{
    [Range(1,5)]
    public float interval;

    private float timer = 0;
    private Animator animator = null;
    private Vector3 prevPosition;

    [SerializeField]
    private Vector3 hipCurrPosition;
    [SerializeField]
    private Vector3 hipPrePosition;
    [SerializeField]
    private Vector3 postTransform;
    [SerializeField]
    private Vector3 finPosition;
    public Rigidbody hips;

    public List<Rigidbody> rigidbodies = new List<Rigidbody>();
    public List<Collider> colliders = new List<Collider>();
    public bool RagdollOn
    {
        get { return !animator.enabled; }
        set
        {
            timer = 0;
            prevPosition = transform.position;

            animator.enabled = !value;
            foreach (Rigidbody r in rigidbodies)
            {
                r.isKinematic = !value;
            }
            foreach (Collider c in colliders)
            {
                c.enabled = !value;
                if(c.enabled)
                {
                    animator.SetTrigger("GetUp");
                }
            }
        }
    }

    // Use this for initialization
    void Start()
    {
        animator = GetComponent<Animator>();
        foreach (Rigidbody r in rigidbodies)
        {
            r.isKinematic = true;
            r.mass = r.mass * 0.01f;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (RagdollOn)
        {
            timer += Time.deltaTime;

            if (timer >= interval)
            {
                timer -= interval;

                if (prevPosition.x > transform.position.x - 1 || prevPosition.x < transform.position.x + 1)
                {
                    if (prevPosition.y > transform.position.y - 1 || prevPosition.y < transform.position.y + 1)
                    {
                        if (prevPosition.z > transform.position.z - 1 || prevPosition.z < transform.position.z + 1)
                        {
                            hipPrePosition = hips.transform.position;

                            foreach (Collider c in colliders)
                            {
                                RaycastHit hit;
                                if (Physics.Raycast(hipPrePosition, -transform.up, out hit, 1))
                                {
                                    if (!hit.collider.CompareTag("Player"))
                                    {
                                        c.transform.position = new Vector3(hipPrePosition.x, hit.point.y + 0.3f, hipPrePosition.z);
                                    }
                                }
                            }

                            postTransform = transform.position;
                            RagdollOn = false;

                            finPosition = transform.position;
                        }
                    }
                }

                prevPosition = transform.position;
            }
        }
        hipCurrPosition = hips.transform.position;
    }
}
