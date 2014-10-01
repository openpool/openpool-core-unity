using UnityEngine;
using UnityEditor;
using System.Collections;

public class OpenPoolMenu : ScriptableObject {
	
	[MenuItem("OpenPool/Online Documents")]
	public static void ShowDocuments ()
	{
		Application.OpenURL("http://www.openpool.cc/");
	}
}
