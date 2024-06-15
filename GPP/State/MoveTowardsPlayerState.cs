using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MoveTowardsPlayerState : State
{


    // implement
    public override State HandleInput(Enemy enemy, Transform player)
    {
        if ( Vector3.Distance(player.position, enemy.transform.position) < enemy.attackRange) 
        {
            enemy.attackRange += 1f;

            return enemy.AttackState;
        }
        if ( Vector3.Distance(player.position, enemy.transform.position) > enemy.visibleRange)
        {
            enemy.visibleRange = 10f;

            return enemy.StrollState;
        }

        return null;
    }

    // implement
    public override void DoAction(Enemy enemy, Transform player)
    {
        enemy.transform.position = Vector3.MoveTowards(enemy.transform.position, player.position, step*Time.deltaTime);
    }

    public override void Enter() 
    { 
        enemy.changeColor(Color.yellow);
    }

    public override void Exit() 
    { 
        
    }
}

