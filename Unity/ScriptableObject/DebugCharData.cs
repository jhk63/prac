using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DebugCharData : MonoBehaviour
{
    public List<MyScriptableObj> myScriptableObjs;

    void Start()
    {
        foreach (var myScriptableObj in myScriptableObjs)
        {
            Debug.Log($"Character Name : {myScriptableObj.myName}");
            Debug.Log($"Character HP : {myScriptableObj.health}");
            Debug.Log($"Character Speed : {myScriptableObj.speed}");
        }
    }
}
