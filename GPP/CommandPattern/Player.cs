using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public float speed { get; set; }
    private bool isReplaying;
    public bool isMoving { get; set; }

    public Vector3 destPos { get; set; }
    public Queue<Command> recordQueue;

    // Start is called before the first frame update
    void Start()
    {
        speed = 5.0f;
        isReplaying = false;
        isMoving = false;

        recordQueue = new Queue<Command>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!isReplaying)
        {
            Command command = HandleInput();
            if (command != null)
            {
                command.Execute();
                recordQueue.Enqueue(command);
            }
        }
        // isReplaying == true
        else
        {
            if (recordQueue.Count > 0)
            {
                recordQueue.Dequeue().Undo();
            }
            else
            {
                isReplaying = false;
                Debug.Log("isReplaying: " + isReplaying);
            }
        }
    }

    Command HandleInput()
    {
        if (isMoving == true)
        {
            return new MoveToCommand(this);
        }

        if (Input.GetMouseButtonDown(1) && recordQueue.Count > 0)
        {
            isReplaying = true;
            Debug.Log("isReplaying: " + isReplaying);
        }
        else if (Input.GetMouseButtonDown(0))
        {
            return new MoveToCommand(this);
        }
        else if (Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.W))
		{
			return new MoveForwardCommand(this);
		}
		else if (Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S))
		{
			return new MoveBackwardCommand(this);
		}
        else if (Input.GetKey(KeyCode.RightArrow) || Input.GetKey(KeyCode.D))
		{
			return new MoveRightCommand(this);
		}
        else if (Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.A))
		{
			return new MoveLeftCommand(this);
		}

        return null;
    }
}
