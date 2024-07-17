using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class ThrowableWeapon : BaseWeapon
{
    public float throwForce;

    public override void Fire()
    {
        // 투척 무기 로직
    }

    public override void Reload()
    {
        // 투척 무기 보충 로직
    }
}
