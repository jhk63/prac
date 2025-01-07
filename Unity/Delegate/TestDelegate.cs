using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestDelegate : MonoBehaviour
{
    // private static TestDelegate _instance;
    // public static TestDelegate Instance { get {return _instance;} }

    public delegate void ChainFunction(int value);
    public static event ChainFunction chain;
    // public event ChainFunction chain;

    // private void Awake() {
    //     if (_instance == null)
    //     {
    //         _instance = this;
    //     }
    // }

    // Start is called before the first frame update
    void Start()
    {
        // Add a Function 
		chain += MessageFirst;
		chain += MessageSecond;
		chain += MessageSecond;
		
		// Remove a Function 
		chain -= MessageSecond;
		
		if (chain != null)
		{
			chain(5);
		}
    }

    // Update is called once per frame
    void MessageFirst(int value)
	{
		Debug.Log($"[Delegate1] My First Message: {value}");
	}
	
	void MessageSecond(int value)
	{
		Debug.Log($"[Delegate2] My Second Message: {value}");
	}
}
