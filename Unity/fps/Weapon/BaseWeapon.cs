using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BaseWeapon : MonoBehaviour
{
    public string weaponName;
    public int damage;

    public abstract void Fire();
    public abstract void Reload();
}
