using UnityEngine;
using System.Collections.Generic;
using System.Text;

namespace Debugger {
	/// <summary>
	/// Global GUI Logger.
	/// </summary>
	[RequireComponent(typeof(GUIText))]
	[AddComponentMenu("Debugger/GlobalLogger")]
	public class GlobalLogger : MonoBehaviour {
		
		[SerializeField]
		int linesCount = 20;
		
		[SerializeField]
		bool showStackTrace = false;
		
		GUIText gui;
		Queue<string> logQueue;
		StringBuilder stringBuilder;
		
		void OnEnable() {
			gui = GetComponent<GUIText>();
			logQueue = new Queue<string>();
			stringBuilder = new StringBuilder();
			// 
			Application.RegisterLogCallback(LogCallback);
		}
		
		void OnDisable() {
			Application.RegisterLogCallback(null);
		}
		
		
		// delegate for Log
		void LogCallback (string condition, string stackTrace, LogType type) {
			
			if(type == LogType.Warning) {
				// yellow color
				condition = "<color=#ffff00ff>" + condition + "</color>";
			}
			else if(type == LogType.Error || type == LogType.Exception) {
				// red color
				condition = "<color=#ff0000ff>" + condition + "</color>";
			}
			
			logQueue.Enqueue(condition + "\n");
			if(showStackTrace) {
				logQueue.Enqueue(stackTrace + "\n");
			}
			
			while(logQueue.Count > linesCount) {
				logQueue.Dequeue();
			}
			
			stringBuilder.Length = 0;
			stringBuilder.Append("====LOG====\n");
			
			foreach(string str in logQueue) {
				stringBuilder.Append(str);
			}
			
			gui.text = stringBuilder.ToString();
		}
	}
}
