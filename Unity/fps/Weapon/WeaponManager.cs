using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WeaponManager : MonoBehaviour
{
    public List<BaseWeapon> weapons;
    private BaseWeapon currentWeapon;

    public void SwitchWeapon(int index)
    {

    }

    public void FireCurrentWeapon()
    {
        currentWeapon.Fire();
    }

    public void ReloadCurrentWeapon()
    {
        currentWeapon.Reload();
    }

}
