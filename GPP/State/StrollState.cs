using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class StrollState : State
{
    Vector3 targetLocation;
    float step = 1f;


    // implement
    public override State HandleInput()
    {
        if (Vector3(player.position, enemy.position) < enemy.visibleRange)
        {
            enemy.visibleRange += 5f;

            return new MoveTowardsPlayerState(enemy, player);
        }

        return null;
    }

    // implement
    public override void DoAction()
    {
        if ( Vector3.Distance(transform.position, targetLocation) < Mathf.Epsilon) 
        { 
            float radius = 3f;
            targetLocation = enemy.transform.position + new Vector3(Random.Range(radius*-1f, radius*1f), 0f, Random.Range(radius*-1f, radius*1f));
        }

        enemy.transform.position = Vector3.MoveTowards(enemy.transform.position, targetLocation, step*Time.deltaTime);
    }

    public override void Enter() 
    { 
        float radius = 5f;
        targetLocation = enemy.transform.position + new Vector3(Random.Range(radius*-1f, radius*1f), 0f, Random.Range(radius*-1f, radius*1f));
        
        enemy.changeColor(Color.white);
    }

    public override void Exit() 
    { 
        
    }
}

