using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Networking;

[System.Serializable]
public class GoogleData
{
    public string order, result, msg, value;
}

public class GoogleSheetManager : MonoBehaviour
{
    const string url = "";
    public GoogleData GD;
    public TMP_InputField IDInput, PWInput, VALUEInput;
    string id, pw;

    // IEnumerator Start()
    // {
        // WWWForm form = new WWWForm();
        // form.AddField("value", "값");

        // UnityWebRequest www = UnityWebRequest.Get(url);
        // UnityWebRequest www = UnityWebRequest.Post(url, form);
        // yield return www.SendWebRequest();

        // string data = www.downloadHandler.text;
        // print(data);
    // }

    bool SetIdPw()
    {
        id = IDInput.text.Trim();
        pw = PWInput.text.Trim();

        if (id == "" || pw == "") return false;
        
        return true;
    }

    public void Register()
    {
        if (!SetIdPw())
        {
            Debug.Log("ID, PW가 비어있습니다.");
            return;
        }

        WWWForm form = new WWWForm();
        form.AddField("order", "register");
        form.AddField("id", id);
        form.AddField("pw", pw);

        StartCoroutine(Post(form));
    }

    public void Login()
    {
        if (!SetIdPw())
        {
            Debug.Log("ID, PW가 비어있습니다.");
            return;
        }

        WWWForm form = new WWWForm();
        form.AddField("order", "login");
        form.AddField("id", id);
        form.AddField("pw", pw);

        StartCoroutine(Post(form));
    }

    void OnApplicationQuit()
    {
        WWWForm form = new WWWForm();
        form.AddField("order", "logout");

        StartCoroutine(Post(form));
    }

    public void SetValue()
    {
        string value = VALUEInput.text.Trim();

        if (value == "")
        {
            Debug.Log("값이 비어있습니다.");
            return;
        }

        WWWForm form = new WWWForm();
        form.AddField("order", "setValue");
        form.AddField("value", VALUEInput.text);

        StartCoroutine(Post(form));
    }

    public void GetValue()
    {
        WWWForm form = new WWWForm();
        form.AddField("order", "GetValue");

        StartCoroutine(Post(form));
    }

    IEnumerator Post(WWWForm form)
    {
        // 반드시 using을 써야한다. 통신을 안하는 경우가 있기 때문에
        using (UnityWebRequest www = UnityWebRequest.Post(url, form))
        {
            yield return www.SendWebRequest();

            if (www.isDone) Debug.Log(www.downloadHandler.text);
            else Debug.Log("웹의 응답이 없습니다.");
        }
    }

    void Response(string json)
    {
        if (string.IsNullOrEmpty(json)) return;

        GD = JsonUtility.FromJson<GoogleData>(json);

        if (GD.result == "ERROR")
        {
            print(GD.order + "을 실행할 수 없습니다. 에러 메시지: " + GD.msg);
            return;
        }

        print(GD.order + "을 실행했습니다. 메시지: " + GD.msg);

        if (GD.order == "getValue")
        {
            VALUEInput.text = GD.value;
        }
    }
}
