using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public Pistol pistol;

    void Update()
    {
        if (Input.GetButtonDown("Fire1"))  // 마우스 왼쪽 버튼
        {
            pistol.Fire();
        }

        if (Input.GetKeyDown(KeyCode.R))  // R 키
        {
            pistol.Reload();
        }
    }
}
