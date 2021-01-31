package prototype;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Vector;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.awt.FileDialog;

//import Test.MyPanel;
public class TeamProject {

	private JFrame mainFrame = new JFrame();
	private JPanel northP, centerP, westP;
	private JTabbedPane tabbedPanel;
	private JToolBar toolBar;

	JLabel statusLabel;

	MakerMouseListener MakerMouse = new MakerMouseListener();
	SelectorMouseListener SelectorMouse = new SelectorMouseListener();

	int IOC = 0;// Index of Component
	boolean MMO = false;// Maker Mouse On

	Vector<MyComponent> VC = new Vector<MyComponent>(); // Vector of Components

	TeamProject() {
		mainFrame.setTitle("Drawing Square");
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setSize(1000, 1000);

		mainFrame.setLayout(new BorderLayout(10, 10));

		mkNorthP();
		mkCenterP();
		mkWestP();
		statusLabel = new JLabel("Status", JLabel.CENTER);
		statusLabel.setSize(350, 100);
		statusLabel.setForeground(Color.blue);
		centerP.add(statusLabel);

		JMenuBar myMenuBar = new JMenuBar();
		JMenu m_File = new JMenu("File");
		JMenu m_Edit = new JMenu("Edit");

		JMenuItem mi_New = new JMenuItem("New");
		mi_New.addActionListener(new NewButtonListener());

		JMenuItem mi_Open = new JMenuItem("Open");
		mi_Open.addActionListener(new OpenButtonListener());

		JMenuItem mi_Save = new JMenuItem("Save");
		mi_Save.addActionListener(new SaveButtonListener());

		JMenuItem mi_ExportJava = new JMenuItem("ExportJava");
		mi_ExportJava.addActionListener(new ExportJavaButtonListener());

		JMenuItem mi_Make = new JMenuItem("Make");
		mi_Make.addActionListener(new MakeButtonListener());

		JMenuItem mi_Delete = new JMenuItem("Delete");
		mi_Delete.addActionListener(new DeleteButtonListener());

		m_File.add(mi_New);
		m_File.add(mi_Open);
		m_File.add(mi_Save);
		m_File.add(mi_ExportJava);
		m_Edit.add(mi_Make);
		m_Edit.add(mi_Delete);

		myMenuBar.add(m_File);
		myMenuBar.add(m_Edit);
		mainFrame.setJMenuBar(myMenuBar);
		mainFrame.setVisible(true);
	}

	void mkNorthP() {
		northP = new JPanel();
		mainFrame.add(northP, BorderLayout.NORTH);
		northP.setLayout(new BorderLayout());

		JButton NewButton = new JButton("New");
		NewButton.addActionListener(new NewButtonListener());

		JButton OpenButton = new JButton("Open");
		OpenButton.addActionListener(new OpenButtonListener());

		JButton SaveButton = new JButton("Save");
		SaveButton.addActionListener(new SaveButtonListener());

		JButton ExportJavaButton = new JButton("ExportJava");
		ExportJavaButton.addActionListener(new ExportJavaButtonListener());

		JButton MakeButton = new JButton("Make");
		MakeButton.addActionListener(new MakeButtonListener());

		JButton DeleteButton = new JButton("Delete");
		DeleteButton.addActionListener(new DeleteButtonListener());

		toolBar = new JToolBar();
		toolBar.setRollover(true);
		northP.add(toolBar);

		toolBar.add(NewButton);
		toolBar.add(OpenButton);
		toolBar.add(SaveButton);
		toolBar.add(ExportJavaButton);
		toolBar.add(MakeButton);
		toolBar.add(DeleteButton);
		northP.setVisible(true);
	}

	void mkCenterP() {
		centerP = new JPanel(null);
		mainFrame.add(centerP, BorderLayout.CENTER);
		centerP.setBackground(Color.white);
		centerP.addMouseListener(MakerMouse);
		centerP.addMouseMotionListener(MakerMouse);
	}

	void mkWestP() {
		westP = new JPanel();
		mainFrame.add(westP, BorderLayout.WEST);
		tabbedPanel = new JTabbedPane();
		tabbedPanel.setPreferredSize(new Dimension(200, 800));
		tabbedPanel.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				for (MyComponent I : VC) {// 선택
					if (I.index - 1 == tabbedPanel.getSelectedIndex())
						I.UCP.setBackground(Color.pink);
					else // 만약 선택된게 있었더라면 선택 취소
						I.UCP.setBackground(Color.LIGHT_GRAY);
				}
			}
		});
		westP.add(tabbedPanel);
	}

	public static void main(String[] args) {
		new TeamProject();
	}

	class NewButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			for (MyComponent I : VC)
				centerP.remove(I.UCP);
			tabbedPanel.removeAll();
			VC.removeAllElements();
			centerP.repaint();
			IOC = 0;
		}
	}

	class OpenButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			FileDialog fd = new FileDialog(new JFrame(), "Open", FileDialog.LOAD);
			fd.setDirectory(System.getProperty("user.dir"));
			fd.setFile("*.json");
			fd.setVisible(true);
			if (fd.getFile() == null) {
				statusLabel.setText("Open Cancelled");
				return;
			}
			new NewButtonListener().actionPerformed(e);
			ParseJSON PJ = new ParseJSON(fd.getDirectory() + fd.getFile());
			JSONArray CompoArray = PJ.getCompoArray();
			for (int i = 0; i < CompoArray.size(); i++) {
				JSONObject CompoInfo = (JSONObject) CompoArray.get(i);

				System.out.println(CompoInfo);

				String name = CompoInfo.get("Name").toString();
				String text = CompoInfo.get("Text").toString();
				int x = Integer.parseInt(CompoInfo.get("X").toString());
				int y = Integer.parseInt(CompoInfo.get("Y").toString());
				int w = Integer.parseInt(CompoInfo.get("W").toString());
				int h = Integer.parseInt(CompoInfo.get("H").toString());
				int type = Integer.parseInt(CompoInfo.get("Type").toString());
				VC.add(new MyComponent(i + 1, name, text, x, y, w, h, type));
			}
			IOC = CompoArray.size();
		}
	}

	class SaveButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			FileDialog fd = new FileDialog(new JFrame(), "Save", FileDialog.SAVE);
			fd.setDirectory(System.getProperty("user.dir"));
			fd.setFile("*.json");
			fd.setVisible(true);
			if (fd.getFile() == null) {
				statusLabel.setText("Save Cancelled");
				return;
			}
			MakeJSON MJ = new MakeJSON();
			for (MyComponent I : VC)
				MJ.InputMyComponent(I);
			MJ.SaveCompoSet(fd.getDirectory() + fd.getFile());
			statusLabel.setText("Save Completed!");
		}
	}

	class ExportJavaButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			FileDialog fd = new FileDialog(new JFrame(), "ExportJava", FileDialog.SAVE);
			fd.setDirectory(System.getProperty("user.dir"));
			fd.setFile("*.java");
			fd.setVisible(true);
			if (fd.getFile() == null) {
				statusLabel.setText("ExportJava Cancelled");
				return;
			}
			FileWriter file;

			String fileName = fd.getFile().substring(0, fd.getName().length() - 4);
			try {
				file = new FileWriter(fd.getDirectory() + fd.getFile());
				file.write("import javax.swing.*;\nimport java.awt.*;\n\npublic class " + fileName
						+ " extends JFrame {\n\t" + fileName + "(){\n\tsetTitle(\"" + fileName
						+ "\");\n\tsetDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);\n\t"
						+ "getContentPane().setBackground(Color.WHITE);\n\tsetLayout(null);\n\t");

				for (MyComponent I : VC) {
					if (I.type == 0)
						file.write("JButton " + I.name + " = new JButton(\"" + I.text + "\");");
					else if (I.type == 1)
						file.write("JLabel " + I.name + " = new JLabel(\"" + I.text + "\");");
					else if (I.type == 2)
						file.write("JCheckBox " + I.name + " = new JCheckBox(\"" + I.text + "\");");
					file.write("\n\t" + I.name + ".setLocation(new Point(" + I.p.x + "," + I.p.y + "));\n\t" + I.name
							+ ".setSize(new Dimension(" + I.d.width + "," + I.d.height + "));\n\t" + I.name
							+ ".setText(\"" + I.text + "\");\n\t" + I.name + ".setOpaque(true);\n\t" + I.name
							+ ".setBackground(Color.LIGHT_GRAY);\n\tadd(" + I.name + ");\n\t");
				}
				file.write("setSize(750, 870);\nsetVisible(true);\n}\npublic static void main(String[] args) {\nnew "
						+ fileName + "();\n}\n}");
				file.flush();
				file.close();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}

	class MakeButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			if (MMO == false) {
				MMO = true;
				statusLabel.setText("Maker Mouse Mode On");
			} else {
				MMO = false;
				statusLabel.setText("Maker Mouse Mode Off");
			}

		}
	}

	class DeleteButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			for (MyComponent I : VC) {
				if (I.index - 1 == tabbedPanel.getSelectedIndex()) {
					centerP.remove(I.UCP);
					I.T_name.setEnabled(false);
					I.T_text.setEnabled(false);
					I.T_w.setEnabled(false);
					I.T_h.setEnabled(false);
					I.T_x.setEnabled(false);
					I.T_y.setEnabled(false);
					I.myComboBox.setEnabled(false);
					VC.removeElement(I);
					mainFrame.repaint();
					statusLabel.setText("Removed Component");
					break;
				}
			}
		}
	}

	class TextListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			for (MyComponent I : VC) {
				if (e.getSource() == null) {
					statusLabel.setText("NumberFormatException");
				} else if (e.getSource() == I.T_name) {
					I.name = e.getActionCommand();
					statusLabel.setText("changed Name");
					I.updata();
					break;
				} else if (e.getSource() == I.T_text) {
					I.text = e.getActionCommand();
					statusLabel.setText("changed Text");
					I.updata();
					break;
				} else if (e.getSource() == I.T_x) {
					I.p.x = Integer.parseInt(e.getActionCommand());
					statusLabel.setText("changed X");
					I.updata();
					break;
				} else if (e.getSource() == I.T_y) {
					I.p.y = Integer.parseInt(e.getActionCommand());
					statusLabel.setText("changed Y");
					I.updata();
					break;
				} else if (e.getSource() == I.T_w) {
					I.d.width = Integer.parseInt(e.getActionCommand());
					statusLabel.setText("changed width");
					I.updata();
					break;
				} else if (e.getSource() == I.T_h) {
					I.d.height = Integer.parseInt(e.getActionCommand());
					statusLabel.setText("changed height");
					I.updata();
					break;
				}
			}
		}
	}

	class MakerMouseListener extends MouseAdapter implements MouseMotionListener {

		Point StartP = null;
		Point EndP = null;

		public void mousePressed(MouseEvent e) {
			if (MMO == false)
				return;
			IOC++;
			StartP = e.getPoint();
			VC.add(new MyComponent(IOC, StartP.x, StartP.y, new Dimension(0, 0)));
		}

		public void mouseReleased(MouseEvent e) {
			if (MMO == false)
				return;
			EndP = e.getPoint();
			VC.lastElement().setSize(EndP.x - StartP.x, EndP.y - StartP.y);
			MMO = false;
			statusLabel.setText("maked Component");
		}

		public void mouseDragged(MouseEvent e) {
			if (MMO == false)
				return;
			EndP = e.getPoint();
			VC.lastElement().setSize(EndP.x - StartP.x, EndP.y - StartP.y);
		}
	}

	class SelectorMouseListener extends MouseAdapter implements MouseMotionListener {
		Point StartP = null;
		Point EndP = null;

		MyComponent SC = null;// Selected Component

		public void mousePressed(MouseEvent e) {
			if (centerP == e.getComponent()) {// 만약 마우스가 센터페널이라면 사이즈 변경을 하면 안된다.
				SC = null;
			}
			StartP = e.getPoint();
			for (MyComponent I : VC) {// 선택
				if (I.UCP == e.getComponent()) {
					SC = I;
					I.UCP.setBackground(Color.pink);
					tabbedPanel.setSelectedIndex(I.index - 1);
				} else {// 만약 선택된게 있었더라면 선택 취소
					I.UCP.setBackground(Color.LIGHT_GRAY);
				}
			}
			System.out.println("StartP : " + StartP);
		}

		public void mouseDragged(MouseEvent e) {
			int type = e.getComponent().getCursor().getType();

			if (centerP == e.getComponent()) {// 만약 마우스가 센터페널이라면 사이즈 변경을 하면 안된다.
				SC = null;
				return;
			}
			EndP = e.getPoint();
			switch (type) {
			case Cursor.MOVE_CURSOR:
				SC.setLocation(e.getComponent().getX() + EndP.x - StartP.x,
						e.getComponent().getY() + EndP.y - StartP.y);
				break;
			case Cursor.SE_RESIZE_CURSOR:
				SC.setSize(EndP.x + 5, EndP.y + 5);
				break;
			}
		}

		public void mouseMoved(MouseEvent e) {
			if (SC == null)
				return;
			else if (SC.UCP == e.getComponent()) {
				if (e.getPoint().distance(SC.SE) < 20) {
					SC.UCP.setCursor(Cursor.getPredefinedCursor(Cursor.SE_RESIZE_CURSOR));
					System.out.println(e.getPoint().distance(SC.SE));
				} else {
					SC.UCP.setCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
				}
			} else {// SC가 존재하고 마우스가 밖에 있을때
				SC.UCP.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
			}

		}
	}

	class MyComponent {
		JComponent UCP;
		String name, text;
		Point p;
		Dimension d;

		int index, type;// type 0: Button, 1: Label, 2: CheckBox

		JPanel TP = new JPanel();// Tabbed_Panel

		JTextField T_name = new JTextField();
		JTextField T_text = new JTextField();
		JTextField T_x = new JTextField();
		JTextField T_y = new JTextField();
		JTextField T_w = new JTextField();
		JTextField T_h = new JTextField();
		JComboBox myComboBox;

		/*
		 * Point S = new Point(); Point N = new Point(); Point W = new Point();
		 * Point E = new Point();
		 */// 안씀
		Point SE = new Point();
		/*
		 * Point SW = new Point(); Point NW = new Point(); Point NE = new
		 * Point();
		 */

		MyComponent(int index, int x, int y, Dimension d) {// 위치, 크기
			UCP = new JButton();
			this.index = index;
			setName("Component" + Integer.toString(index));
			setText("");
			setLocation(new Point(x, y));
			setSize(d);
			String[] comboString = { "Button", "Label", "CheckBox" };
			myComboBox = new JComboBox(comboString);
			System.out.println("npd-c");
			construct();
		}

		MyComponent(int index, String name, String text, int x, int y, int w, int h, int type) {
			String[] comboString = { "Button", "Label", "CheckBox" };
			myComboBox = new JComboBox(comboString);
			if (type == 0) {
				this.type = type;
				UCP = new JButton();
				myComboBox.setSelectedIndex(0);
			} else if (type == 1) {
				this.type = type;
				UCP = new JLabel();
				myComboBox.setSelectedIndex(1);
			} else if (type == 2) {
				this.type = type;
				UCP = new JCheckBox();
				myComboBox.setSelectedIndex(2);
			}
			this.index = index;
			setName(name);
			setText(text);
			setLocation(new Point(x, y));
			setSize(new Dimension(w, h));
			System.out.println("npd-c");
			construct();
		}

		public void setName(String name) {
			this.name = name;
			T_name.setText(name);
		}

		public void setText(String text) {
			this.text = text;
			T_text.setText(text);
			if (UCP.getClass().getName() == "javax.swing.JButton") {
				JButton RUCP = (JButton) UCP;// real your component
				RUCP.setText(text);
			} else if (UCP.getClass().getName() == "javax.swing.JLabel") {
				JLabel RUCP = (JLabel) UCP;// real your component
				RUCP.setText(text);
			} else if (UCP.getClass().getName() == "javax.swing.JCheckBox") {
				JCheckBox RUCP = (JCheckBox) UCP;// real your component
				RUCP.setText(text);
			}
		}

		public void setLocation(Point p) {
			this.p = p;
			T_x.setText(Integer.toString(p.x));
			T_y.setText(Integer.toString(p.y));
			UCP.setLocation(p);
		}

		public void setLocation(int x, int y) {
			p.setLocation(x, y);
			T_x.setText(Integer.toString(x));
			T_y.setText(Integer.toString(y));
			UCP.setLocation(x, y);
		}

		public void setSize(Dimension d) {
			this.d = d;
			T_w.setText(Integer.toString(d.width));
			T_h.setText(Integer.toString(d.height));
			UCP.setSize(d);
			updateCoordinate();
		}

		public void setSize(int w, int h) {
			d.setSize(w, h);
			T_w.setText(Integer.toString(d.width));
			T_h.setText(Integer.toString(d.height));
			UCP.setSize(w, h);
			updateCoordinate();
		}

		private void updateCoordinate() {
			/*
			 * S.setLocation(d.width / 2, d.height); N.setLocation(d.width / 2,
			 * 0); W.setLocation(0, d.height / 2); E.setLocation(d.width,
			 * d.height / 2);
			 */
			SE.setLocation(d.width, d.height);
			/*
			 * SW.setLocation(0, d.height); NW.setLocation(0, 0);
			 * NE.setLocation(d.width, 0);
			 */
		}

		public void updata() {
			setName(name);
			setText(text);
			setLocation(p);
			setSize(d);
			
			System.out.println(name + " ," + text);
		}

		public void construct() {
			mkTab();
			centerP.add(UCP);
			T_name.addActionListener(new TextListener());
			T_text.addActionListener(new TextListener());
			T_x.addActionListener(new TextListener());
			T_y.addActionListener(new TextListener());
			T_w.addActionListener(new TextListener());
			T_h.addActionListener(new TextListener());
			myComboBox.addItemListener(new ItemListener() {
				public void itemStateChanged(ItemEvent e) {
					UCP.setVisible(false);
					if (e.getItem().toString() == "Button") {
						System.out.println("changed Button");
						UCP = new JButton();
						type = 0;
					} else if (e.getItem().toString() == "Label") {
						System.out.println("changed Label");
						UCP = new JLabel();
						type = 1;
					} else if (e.getItem().toString() == "CheckBox") {
						System.out.println("changed CheckBox");
						UCP = new JCheckBox();
						type = 2;
					}
					centerP.add(UCP);
					updata();
					System.out.println(UCP.getClass());
					UCP.setOpaque(true);
					UCP.setBackground(Color.LIGHT_GRAY);
					UCP.addMouseMotionListener(SelectorMouse);
					UCP.addMouseListener(SelectorMouse);
				}
			});
			UCP.setOpaque(true);
			UCP.setBackground(Color.LIGHT_GRAY);
			UCP.addMouseMotionListener(SelectorMouse);
			UCP.addMouseListener(SelectorMouse);
		}

		void mkTab() {
			TP.setPreferredSize(new Dimension(200, 100));
			tabbedPanel.addTab(Integer.toString(index), TP);
			System.out.println("Size Of VC: " + VC.size());
			TP.setLayout(new GridLayout(0, 2));

			TP.add(new JLabel("Variable Name : "));
			TP.add(T_name);
			TP.add(new JLabel("Text : "));
			TP.add(T_text);
			TP.add(new JLabel("x : "));
			TP.add(T_x);
			TP.add(new JLabel("y : "));
			TP.add(T_y);
			TP.add(new JLabel("width : "));
			TP.add(T_w);
			TP.add(new JLabel("height : "));
			TP.add(T_h);
			TP.add(new JLabel("Type : "));
			TP.add(myComboBox);

			System.out.println("텝을만들어");
		}
	}
}