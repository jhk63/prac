using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Command
{
    Player player;
    public Command(Player player)
    {
        this.player = player;
    }
    public abstract void Execute();
    public abstract void Undo();
}
