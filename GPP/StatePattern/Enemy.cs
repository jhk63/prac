using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Enemy : MonoBehaviour
{

        Vector3 targetLocation;

        Transform player;

        float step;
        
        float visibleRange {get; set;}

        float attackRange {get; set;}

        Renderer rend;

        [SerializeField] public float hp;

        protected enum EnemyFSM
        {
                Stroll = 0,
                MoveTowardsPlayer,
                Attack ,
                Flee,
                End
        }

        State state;


        public Vector3 getRandomLocation(float radius)
        {
                return transform.position + new Vector3(Random.Range(radius*-1f, radius*1f), 0f, Random.Range(radius*-1f, radius*1f));
        }

        public void changeColor(Color newColor)
        {
                rend.material.SetColor("_Color", newColor);
        }

        void Start()
        {
            player = GameObject.Find("Player").transform;
            rend = GetComponent<Renderer>();
            changeColor(Color.white);

            hp = 100f;
            step = 1f;

            // state = strollState;
            state = StrollState(this, player);
            state.Enter();
        }

        //Update the enemy by giving it a new state

        void Update()
        {
            State state_ = state.HandleInput();
            if (state_ != null)
            {
                state.Exit();
                state = state_
                state.Enter();
            }

            state.DoAction();
        }
}

