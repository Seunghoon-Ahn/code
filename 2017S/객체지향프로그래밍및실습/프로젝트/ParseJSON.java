package prototype;

import java.io.FileNotFoundException;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class ParseJSON {
	JSONParser parser;
	Object obj;
	private JSONArray CompoArray;

	public ParseJSON(String fileroot) {
		try {
			parser = new JSONParser();
			obj = parser.parse(new FileReader(fileroot));
			CompoArray = (JSONArray) obj;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public JSONArray getCompoArray(){
		return CompoArray;
	}

}
