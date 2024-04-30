using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveForwardCommand : Command
{
    private Player player;
    Vector3 beforePos;

    public MoveForwardCommand(Player player) : base(player)
    {
        this.player = player;
        beforePos = player.transform.position;
    }

    public override void Execute()
    {
        player.transform.Translate(Vector3.forward * player.speed * Time.deltaTime);
    }

    public override void Undo()
    {
        player.transform.position = beforePos;
    }
}
