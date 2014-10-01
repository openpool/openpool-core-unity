// --
// The MIT License
// 
// Copyright (c) 2013 tatsuhiko yamamura
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ---
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using MiniJSON;
using UnityEditor.Sprites;
using System.IO;

public class JsonSplitSprite : AssetPostprocessor
{
	static void OnPostprocessAllAssets (
		string[] importedAssets, 
		string[] deletedAssets, 
		string[] movedAssets, 
		string[] movedFromAssetPaths)
	{
		foreach (var asset in importedAssets) {
			if (!Path.GetExtension (asset).Equals (".txt")) {
				continue;
			}

			TextAsset json = AssetDatabase.LoadAssetAtPath (asset, typeof(TextAsset)) as TextAsset;
			var pngPath = asset.Substring (0, asset.Length - 4) + ".png";
			if (!File.Exists (pngPath)) {
				continue;
			}

			SplitSpriteWithJson (pngPath, json.text);
		}
	}

	static void SplitSpriteWithJson (string imagePath, string json)
	{
		// check texture type.
		var importer = (TextureImporter)TextureImporter.GetAtPath (imagePath);
		if( importer.textureType != TextureImporterType.Sprite){
			return;
		}

		// read frame
		var jsonData = (Dictionary<string, object>)Json.Deserialize (json);
		var spriteFrames = (Dictionary<string, object>)jsonData ["frames"];
		
		// read meta file
		var meta = (Dictionary<string, object>)jsonData ["meta"];
		var size = (Dictionary<string, object>)meta ["size"];
		var height = int.Parse (size ["h"].ToString ());
		
		// json to meta
		List<SpriteMetaData> metas = new List<SpriteMetaData> ();
		foreach (string spriteName in spriteFrames.Keys) {
			var dic = (Dictionary<string, object>)spriteFrames [spriteName];
			var metadata = JsonToSpriteMetadata (spriteName, height, (Dictionary<string, object>)dic ["frame"]);
			metas.Add (metadata);
		}
		// import
		importer.spriteImportMode = SpriteImportMode.Multiple;
		importer.spritesheet = metas.ToArray ();
		
		// appry
		EditorUtility.SetDirty (importer);
		AssetDatabase.ImportAsset (imagePath, ImportAssetOptions.ForceUncompressedImport);
	}

	static SpriteMetaData JsonToSpriteMetadata (string spriteName, int height, Dictionary<string, object> frame)
	{
		SpriteMetaData meta = new SpriteMetaData ();
		int x = int.Parse (frame ["x"].ToString ());
		int y = int.Parse (frame ["y"].ToString ());
		int w = int.Parse (frame ["w"].ToString ());
		int h = int.Parse (frame ["h"].ToString ());
		meta.name = spriteName;
		meta.rect = new Rect (x, height - (y + h), w, h);
		meta.pivot = new Vector2 (0.5f, 0.5f);
		return meta;
	}
}