package prototype;

import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

class MakeJSON {
	JSONArray CompoArray;//Info < Array
	JSONObject CompoInfo;

	MakeJSON() {
		CompoArray = new JSONArray();
	}

	void InputMyComponent(TeamProject.MyComponent mc) {
		CompoInfo = new JSONObject();
		CompoInfo.put("Name", mc.name);
		CompoInfo.put("Text", mc.text);
		CompoInfo.put("X", mc.p.x);
		CompoInfo.put("Y", mc.p.y);
		CompoInfo.put("W", mc.d.width);
		CompoInfo.put("H", mc.d.height);
		CompoInfo.put("Type", mc.type);
		CompoArray.add(CompoInfo);
		System.out.println(CompoArray.toString());
	}

	void SaveCompoSet(String fileroot) {		
		FileWriter file;
		try {
			System.out.println(CompoArray.toString());
			file = new FileWriter(fileroot);
			file.write(CompoArray.toString());
			file.flush();
			file.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}