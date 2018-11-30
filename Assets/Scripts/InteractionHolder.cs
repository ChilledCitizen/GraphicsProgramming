using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InteractionHolder : MonoBehaviour
{

    public float radiusModifier = 1;
    [SerializeField]
    GameObject[] objects;
    Vector4[] positions = new Vector4[100];


    void Start()
    {

        foreach (var o in objects)
        {

            Shader.SetGlobalFloat("_Radius", o.GetComponent<Renderer>().bounds.extents.magnitude * radiusModifier);

        }
    }

    // Update is called once per frame
    void Update()
    {

        for (int i = 0; i < objects.Length; i++)
        {
            positions[i] = objects[i].transform.position;
        }
        Shader.SetGlobalFloat("_PositionArray", objects.Length);
        Shader.SetGlobalVectorArray("_Positions", positions);

    }
}