using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pistol : RangedWeapon
{
    public float fireRate = 0.5f;
    private float nextFireTime = 0f;

    public ParticleSystem muzzleFlash;

    public override void Fire()
    {
        if (Time.time >= nextFireTime && ammo > 0)
        {
            PerformRaycast();
            ammo--;
            nextFireTime = Time.time + fireRate;
            
            Debug.Log($"Pistol fired. Ammo left: {ammo}");
        }
        else if (ammo <= 0)
        {
            Debug.Log("Pistol is empty. Reload required.");
        }
    }

    private void PerformRaycast()
    {
        RaycastHit hit;
        if (Physics.Raycast(transform.position, transform.forward, out hit, range))
        {
            Debug.Log($"Hit object at position: {hit.point}");
            // 타격 효과나 데미지 적용 로직 추가
        }
        else
        {
            Debug.Log("Pistol shot missed.");
        }

        muzzleFlash.Play();
    }

    public override void Reload()
    {
        ammo = maxAmmo;
        Debug.Log($"Pistol reloaded. Ammo: {ammo}");
    }
}
