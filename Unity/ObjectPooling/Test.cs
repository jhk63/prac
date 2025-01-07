using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    bool cubeActive = false;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            cubeActive = !cubeActive;
            // GameObject cube = BrackeysObjPoller.SpawnFromPool("Cube", gameObject.transform.position);
            // cube.GetComponent<Cube>().Setup(Random.ColorHSV(0, 1, 0.5f, 1, 1, 1));
        }
    }

    void FixedUpdate()
    {
        if (cubeActive)
        {
            BrackeysObjPoller.SpawnFromPool<Cube>("Cube", gameObject.transform.position)
                .Setup(Random.ColorHSV(0, 1, 0.5f, 1, 1, 1));
        }
    }
}
