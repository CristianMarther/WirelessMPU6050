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

    Vector3 pie_Izq;
    Vector3 rodilla_Izq;
    Vector3 pierna_Izq;
    Vector3 pierna_Der;
    Vector3 pie_Der;
    Vector3 rodilla_Der;

    public static float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;
    public static float h = 0, i = 0, j = 0, k = 0, l = 0, m1 = 0, n = 0;

    SerialPort port = new SerialPort("COM3", 230400);

    string message = "h";

    void Start()
    {

        port.Open();
        port.ReadTimeout = 1;

        pie_Izq = PieL.eulerAngles;
        rodilla_Izq = TibiaL.eulerAngles;
        pierna_Izq = FemurL.eulerAngles;
        pierna_Der = FemurD.eulerAngles;
        pie_Der = PieD.eulerAngles;
        rodilla_Der = TibiaD.eulerAngles;

        //Debug.Log(pierna_Izq[0]);

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
        k = float.Parse(unoL[10]);
        l = float.Parse(unoL[11]);
        m1 = float.Parse(unoL[12]);
        n = float.Parse(unoL[13]);

        if (a != double.NaN && b != double.NaN && c != double.NaN && d != double.NaN && e != double.NaN
            && f != double.NaN && g != double.NaN && h != double.NaN && i != double.NaN && j != double.NaN
            && k != double.NaN && l != double.NaN && m1 != double.NaN && n != double.NaN)
        {
            //Debug.Log(a);
           //Vector3 pie_Izq_aux = new Vector3(pie_Izq[0] + b, pie_Izq[1] + a, pie_Izq[2]);
           //Vector3 rodilla_Izq_aux = new Vector3(rodilla_Izq[0] + d, rodilla_Izq[1], rodilla_Izq[2]);
           //Vector3 pierna_Izq_aux = new Vector3( 1.99f, pierna_Izq[1] + e, pierna_Izq[2]);

            //rodilla_Izq[0] = d;
            //rodilla_Izq[1] = c;

            //pierna_Izq[0] = f;
            //pierna_Izq[1] = e;

            PieL.eulerAngles = new Vector3(pie_Izq[0] + b, pie_Izq[1] + a, pie_Izq[2]);
            TibiaL.eulerAngles = new Vector3(rodilla_Izq[0] + d, rodilla_Izq[1], rodilla_Izq[2]);
            FemurL.eulerAngles = new Vector3(pierna_Izq[0] + f, pierna_Izq[1] + e, pierna_Izq[2]);

            //PieD.eulerAngles = new Vector3(pie_Der[0] + h, pie_Der[1] + g, pie_Der[2]);
            //TibiaD.eulerAngles = new Vector3(rodilla_Der[0] + j, rodilla_Der[1], rodilla_Der[2]);
            //FemurD.eulerAngles = new Vector3(pierna_Der[0] + l, pierna_Der[1] + k, pierna_Der[2]);

            //Debug.Log(pierna_Izq[0]);

        }

    }

}
