using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Cube : MonoBehaviour
{
    public int value;

    public string text;

    public bool toggle;

    public bool[] pos = new bool[] { true, true, true};

    public int intValue;
    public float floatValue;

    public Vector2 scroll;

    public AnimationCurve curveX = AnimationCurve.Linear(0, 0, 1, 1);

    public void SetCurves(AnimationCurve xC)
    {
        curveX = xC;
    }

    void Update()
    {
        transform.position = new Vector3(curveX.Evaluate(Time.time), 0, 0);
    }
}
