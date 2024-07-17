using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class MeleeWeapon : BaseWeapon
{
    public float attackRange;

    public override void Fire()
    {
        // 근접 무기 공격 로직
    }

    public override void Reload()
    {
        // 근접 무기는 재장전이 필요 없음
    }
}
