using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class RangedWeapon : BaseWeapon
{
    public int ammo;
    public int maxAmmo;
    public float range;

    public override void Fire()
    {
        // 원거리 무기 공격 로직
    }

    public override void Reload()
    {
        // 원거리 무기 재장전 로직
    }
}
