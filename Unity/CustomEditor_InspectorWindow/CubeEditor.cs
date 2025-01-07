using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(Cube))]
public class CubeEditor : Editor
{
    Cube cube;

    #pragma warning disable CS0414
    bool posGroupEnable = true;
    #pragma warning restore CS0414

    void OnEnable()
    {
        cube = target as Cube;
    }

    public override void OnInspectorGUI()
    {
        // 기본적으로 인스펙터에서 나오는 GUI
        /*
        base.OnInspectorGUI();
        DrawDefaultInspector();
        */

        /*
        cube.value = EditorGUILayout.IntField(cube.value);
        cube.value = EditorGUILayout.IntField("Value(Int) ", cube.value);
        cube.value = EditorGUILayout.IntField(cube.value, GUILayout.Width(100), GUILayout.Height(100));
        cube.value = EditorGUILayout.IntField(cube.value,  GUILayout.ExpandWidth(false));
        */


        //////////////////////////////////////////////////////////////////////////
        //////// Box
        //////////////////////////////////////////////////////////////////////////
        /*
        GUILayout.Box("박스");
        GUILayout.Box(Resources.Load<Texture2D>("Crown"), GUILayout.Width(100), GUILayout.Height(100));
        */


        //////////////////////////////////////////////////////////////////////////
        //////// Button | Bool 값을 반환한다.
        //////////////////////////////////////////////////////////////////////////
        /*
        GUILayout.Button("버튼", GUILayout.MinWidth(100), GUILayout.MaxHeight(60));
        GUILayout.Button("버튼2", GUILayout.ExpandWidth(false));

        if(GUILayout.Button("버튼", GUILayout.MinWidth(100), GUILayout.MaxHeight(60))) Debug.Log("버튼 눌림!");
        if(GUILayout.Button("버튼2", GUILayout.ExpandWidth(false))) Debug.Log("버튼2 눌림!");

        if(GUILayout.RepeatButton("버튼", GUILayout.MinWidth(100), GUILayout.MaxHeight(60))) Debug.Log("버튼 눌림!");
        */


        //////////////////////////////////////////////////////////////////////////
        //////// Toggle | 큐브에서 참조해서 토글을 저장해야 저장이 된다.
        //////////////////////////////////////////////////////////////////////////
        /*
        cube.toggle = GUILayout.Toggle(cube.toggle, "토글");
        cube.toggle = EditorGUILayout.ToggleLeft("토글", cube.toggle);
        cube.toggle = EditorGUILayout.Toggle("토글", cube.toggle);

        // Toggle Group
        posGroupEnable = EditorGUILayout.BeginToggleGroup("Align position", posGroupEnable);
        cube.pos[0] = EditorGUILayout.Toggle("x", cube.pos[0]);
        cube.pos[1] = EditorGUILayout.Toggle("y", cube.pos[1]);
        cube.pos[2] = EditorGUILayout.Toggle("z", cube.pos[2]);
        EditorGUILayout.EndToggleGroup();
        */

        //////////////////////////////////////////////////////////////////////////
        //////// Label
        //////////////////////////////////////////////////////////////////////////
        /*
        EditorGUILayout.LabelField("라벨");
        EditorGUILayout.SelectableLabel("복사 가능한 라벨");

        EditorGUILayout.BeginHorizontal();
        EditorGUILayout.PrefixLabel("앞 라벨");
        cube.value = EditorGUILayout.IntField(cube.value);
        cube.value = EditorGUILayout.IntField(cube.value);
        EditorGUILayout.EndHorizontal();
        */


        //////////////////////////////////////////////////////////////////////////
        //////// Text Field
        //////////////////////////////////////////////////////////////////////////
        /*
        cube.text = GUILayout.TextField(cube.text);
        cube.text = EditorGUILayout.TextField("텍스트", cube.text);
        cube.text = EditorGUILayout.PasswordField("비밀번호 텍스트", cube.text);
        cube.text = EditorGUILayout.DelayedTextField("딜레이 텍스트", cube.text);

        cube.text = EditorGUILayout.TextArea(cube.text);
        cube.text = EditorGUILayout.TextArea(cube.text, GUILayout.Height(50));  // 텍스트 필드 영역 고정
        */


        //////////////////////////////////////////////////////////////////////////
        //////// Slider Field
        //////////////////////////////////////////////////////////////////////////
        /*
        base.OnInspectorGUI();

        cube.floatValue = GUILayout.HorizontalSlider(cube.floatValue, 0f, 10f, GUILayout.Height(20));
        cube.floatValue = GUILayout.VerticalSlider(cube.floatValue, 10f, 0f, GUILayout.Height(100));

        cube.floatValue = EditorGUILayout.Slider("Slider", cube.floatValue, 0f, 10f);
        cube.intValue = EditorGUILayout.IntSlider(cube.intValue, 0, 10);
        */


        //////////////////////////////////////////////////////////////////////////
        //////// Scroll Field
        //////////////////////////////////////////////////////////////////////////
        /*
        base.OnInspectorGUI();

        cube.floatValue = GUILayout.HorizontalScrollbar(cube.floatValue, 2f, 0f, 10f);
        cube.floatValue = GUILayout.VerticalScrollbar(cube.floatValue, 2f, 10f, 0f);

        cube.scroll = EditorGUILayout.BeginScrollView(cube.scroll, GUILayout.Width(100), GUILayout.Height(100));
        GUILayout.Button("버튼", GUILayout.Width(150), GUILayout.Height(100));
        GUILayout.Button("버튼", GUILayout.Height(100));
        EditorGUILayout.EndScrollView();
        */


        //////////////////////////////////////////////////////////////////////////
        //////// Scroll Field
        //////////////////////////////////////////////////////////////////////////
        
        cube.curveX = EditorGUILayout.CurveField("Animation on X", cube.curveX);
        cube.SetCurves(cube.curveX);

    }
}
