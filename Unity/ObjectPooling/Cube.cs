using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cube : MonoBehaviour
{
    [SerializeField] Rigidbody rigid;
    [SerializeField] Renderer render;

    [SerializeField] float upForce = 1f;
    [SerializeField] float sideForce = 0.1f;

    void OnEnable()
    {
        float xForce = Random.Range(-sideForce, sideForce);
        float yForce = Random.Range(upForce * 0.5f, upForce);
        float zForce = Random.Range(-sideForce, sideForce);

        Vector3 force = new Vector3(xForce, yForce, zForce);
        rigid.velocity = force;

        Invoke(nameof(DeactiveDelay), 5);
    }

    public void Setup(Color color)
    {
        render.material.color = color;
    }

    void DeactiveDelay() => gameObject.SetActive(false);

    void OnDisable()
    {
        BrackeysObjPoller.ReturnToPool(gameObject);
        CancelInvoke();
    }
}
