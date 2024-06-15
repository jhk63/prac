using System.Collections;
using System.Collections.Generic;
using UnityEngine;


// case 1
// 인터페이스에서 선언되는 함수는 모두 자동으로 public 과 virtual 속성을 띈다
public interface IState : MonoBehaviour
{

    IState HandIsInput();

    void DoAction();
}

// case 2
// 추상 클래스
// abstract ? virtual ? 오버라이딩할 때 차이
public abstract class State
{
    protected Enemy enemy;
    protected Player player;


    public State(Enemy enemy, Transform player) { this.enemy=enemy; this.player=player; }

    public abstract State HandleInput();

    public abstract void DoAction();

    public virtual void Enter() { }

    public virtual void Exit() { }
}

