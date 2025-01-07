using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventDelegate : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        TestDelegate.chain += MessageCheck;
        // TestDelegate.Instance.chain += MessageCheck;

    }

    void MessageCheck(int value)
    {
        if (value == 5)
        {
            Debug.Log($"[Delegate3] Message Check: this is a value 5");
        } else
        {
            Debug.Log($"[Delegate3] Message Check: this is not a value 5");
        }
    }
}
