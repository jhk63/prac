using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveToCommand : Command
{
    Player player;
    Vector3 beforePos;

    Vector3 mousePos;
    Vector3 destPos;

    public MoveToCommand(Player player) : base(player)
    {
        this.player = player;
        beforePos = player.transform.position;
        this.destPos = player.destPos;
    }
    
    public void FindMousePos()
    {
        RaycastHit hit;
        var ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        if (Physics.Raycast(ray, out hit, 100f))
        {
            destPos = new Vector3(hit.point.x, player.transform.position.y, hit.point.z);
        }
        
        // Debug.Log(destPos);
        player.destPos = destPos;
    }

    public override void Execute()
    {
        if (player.isMoving == false)
        {
            player.isMoving = true;
            Debug.Log("isMoving: " + player.isMoving);
            FindMousePos();
        }

        if (player.transform.position == destPos)
        {
            player.isMoving = false;
            Debug.Log("isMoving: " + player.isMoving);
        }

        player.transform.position = Vector3.MoveTowards(player.transform.position, destPos, player.speed * Time.deltaTime);
    }

    public override void Undo()
    {
		player.transform.position = beforePos;
		// player.transform.position = Vector3.MoveTowards(player.transform.position, beforePos, 0.1f);
	}
}
