using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class AttackState : State
{
    Vector3 targetLocation;


    // implement
    public override State HandleInput()
    {
        if (enemy.hp < 20f) 
        {
            targetLocation = enemy.transform.position + (enemy.transform.position - player.position).normalized * 5f;
            enemy.changeColor(Color.green);
            
            return new FleeState(enemy, player);
        }
        if ( Vector3.Distance(player.position, enemy.transform.position) > attackRange)
        {
            enemy.attackRange -= 1f;
            enemy.changeColor(Color.yellow);
            
            return new MoveTowardsPlayerState(enemy, player);
        }

        return null;
    }

    // implement
    public override void DoAction()
    {
        
    }

    public override void Enter() 
    { 
        enemy.changeColor(Color.red);
    }

    public override void Exit() 
    { 
        
    }
}

