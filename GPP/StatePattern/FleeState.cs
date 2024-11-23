using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class FleeState : State
{
    Vector3 targetLocation;


    // implement
    public override State HandleInput()
    {
        if (enemy.hp > 60f)
        {
            targetLocation = enemy.transform.position + (enemy.transform.position - player.position).normalized * 5f;

            return new AttackState(enemy, player);
        }

        return null;
    }

    // implement
    public override void DoAction()
    {
        if ( Vector3.Distance(enemy.transform.position, targetLocation) < Mathf.Epsilon) 
        {
            targetLocation = enemy.transform.position + (enemy.transform.position - player.position).normalized * 5f;
        }

        enemy.hp += 0.02f;
        enemy.transform.position = Vector3.MoveTowards(enemy.transform.position, targetLocation, step* Time.deltaTime);
    }

    public override void Enter() 
    { 
        targetLocation = enemy.transform.position + (enemy.transform.position - player.position).normalized * 5f;
        enemy.changeColor(Color.green);
    }

    public override void Exit() 
    { 
        
    }
}

