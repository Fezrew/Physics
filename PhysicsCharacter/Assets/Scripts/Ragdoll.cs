using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Ragdoll : MonoBehaviour
{
    private float timer = 0;
    public float interval;
    private Animator animator = null;
    private Vector3 prevPosition;
    public Transform hips;
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
                            foreach (Collider c in colliders)
                            {
                                c.transform.position = new Vector3(hips.position.x, hips.position.y + 1, hips.position.z);
                            }
                            RagdollOn = false;
                        }
                    }
                }

                prevPosition = transform.position;
            }
        }
    }
}
