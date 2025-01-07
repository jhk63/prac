using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using UnityEngine;

[CreateAssetMenu(fileName = "NewCharacterData", menuName = "CharacterData", order = 1)]
public class MyScriptableObj : ScriptableObject
{
    public string myName;
    public int health;
    public int speed;
}
