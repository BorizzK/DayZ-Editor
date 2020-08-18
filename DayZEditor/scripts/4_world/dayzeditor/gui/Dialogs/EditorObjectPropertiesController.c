static ref EditorPropertiesController m_EditorPropertiesController;
EditorPropertiesController GetEditorPropertiesController() { return m_EditorPropertiesController; }


class EditorPropertiesController: Controller
{
	private EditorObject m_EditorObject;
	
	string TitleText;
	bool CollapseGeneral = true;
	
	EditBoxWidgetDataF pos_x, pos_y, pos_z;
	EditBoxWidgetDataF rot_x, rot_y, rot_z;
	
	void EditorPropertiesController()
	{
		m_EditorPropertiesController = this;
	}
	
	override void OnWidgetScriptInit(Widget w)
	{
		super.OnWidgetScriptInit(w);		
		TitleText = "Object Properties";
		
	}
	
	void SetEditorObject(EditorObject editor_object)
	{
		m_EditorObject = editor_object;
		SetPosition(m_EditorObject.GetPosition());
		OnPropertyChanged("pos_x");
		OnPropertyChanged("pos_y");
		OnPropertyChanged("pos_z");
		
		OnPropertyChanged("rot_x");
		OnPropertyChanged("rot_y");
		OnPropertyChanged("rot_z");
	}
	
	void SetPosition(vector position)
	{
		pos_x = position[0].ToString();
		pos_y = position[1].ToString();
		pos_z = position[2].ToString();
	}
	
	void SetOrientation(vector orientation)
	{
		rot_x = orientation[0].ToString();
		rot_y = orientation[1].ToString();
		rot_z = orientation[2].ToString();
	}
	
	
	
	vector GetPosition()
	{
		StringEvaluater eval();		
		return Vector(eval.Parse(pos_x), eval.Parse(pos_y), eval.Parse(pos_z));
	}
	
	vector GetOrientation()
	{
		StringEvaluater eval();
		return Vector(eval.Parse(rot_x), eval.Parse(rot_y), eval.Parse(rot_z)); 
	}
	
	override void OnPropertyChanged(string property_name)
	{
		m_EditorObject.SetPosition(GetPosition());
		super.OnPropertyChanged(property_name);
	}
}
