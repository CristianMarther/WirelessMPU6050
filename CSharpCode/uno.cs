using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class MoverCuerpo : MonoBehaviour
{
    public float speed = 10.0f;
    public float rotationSpeed = 10.0f;
    // Start is called before the first frame update
    public Transform FemurL;
    public Transform FemurD;
    public Transform TibiaL;
    public Transform TibiaD;
    public Transform PieL;
    public Transform PieD;
    public Transform DedoPieL;
    public Transform DedoPieD;

    public static float a = 0, b = 0;

    SerialPort port = new SerialPort("COM13", 230400);

    string message = "h";

    void Start()
    {

        port.Open();
        port.ReadTimeout = 1;

    }

    // Update is called once per frame
    void Update()
    {

        if (port.IsOpen)
        {
            try
            {
                message = port.ReadLine();
                datos_uno(message);
            }
            catch
            {

            }

        }

    }

    public void datos_uno(string m)
    {
        string[] unoL;
        unoL = m.Split(',');

        a = float.Parse(unoL[0]);
        b = float.Parse(unoL[1]);
        c = float.Parse(unoL[2]);
        d = float.Parse(unoL[3]);
        e = float.Parse(unoL[4]);
        f = float.Parse(unoL[5]);
        g = float.Parse(unoL[6]);
        h = float.Parse(unoL[7]);
        i = float.Parse(unoL[8]);
        j = float.Parse(unoL[9]);
        k = float.Parse(unoL[0]);
        l = float.Parse(unoL[1]);
        m = float.Parse(unoL[2]);
        n = float.Parse(unoL[3]);

        if (a != double.NaN && b != double.NaN && c != double.NaN && d != double.NaN && e != double.NaN
            && f != double.NaN && g != double.NaN && h != double.NaN && i != double.NaN && j != double.NaN
            && k != double.NaN && l != double.NaN && m != double.NaN && n != double.NaN)
        {
            //Debug.Log(a);

            Vector3 uno = new Vector3(PieL.eulerAngles[0], PieL.eulerAngles[1], PieL.eulerAngles[2]);

            uno[0] = b;
            uno[1] = a;

            PieL.eulerAngles = uno;
        }
           

        

    }

}
