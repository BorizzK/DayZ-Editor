
class DialogBase: ScriptView
{
	// Private members
	private DialogResult m_DialogResult = DialogResult.None;

	// Controller
	protected DialogBaseController m_DialogBaseController;
	
	// View Properties	
	protected WrapSpacerWidget WindowDragWrapper;
	
	void DialogBase(Widget parent = null, string title = "")
	{
		m_DialogBaseController = DialogBaseController.Cast(GetController());
		
		m_DialogBaseController.Title = title;
		m_DialogBaseController.NotifyPropertyChanged("Title");
		m_LayoutRoot.Show(false);
	}
	
	DialogResult ShowDialog()
	{
		Trace("ShowDialog");
		m_LayoutRoot.Show(true);
		while (m_DialogResult == DialogResult.None) {
			Sleep(1);
		}
		
		Log("DialogResult: %1", typename.EnumToString(DialogResult, m_DialogResult));
		return m_DialogResult;
	}
	
	void CloseDialog(DialogResult dialog_result = DialogResult.Cancel)
	{
		Trace("CloseDialog");
		m_DialogResult = dialog_result;
		delete this;
	}
	
	void AddContent(ref ScriptView content)
	{
		content.SetParent(this);
		m_DialogBaseController.DialogContentData.Insert(content);
	}
	
	void AddButton(ref DialogButton button)
	{
		button.SetParent(this);
		m_DialogBaseController.DialogButtonData.Insert(button);
	}
	
	private float m_OffsetX, m_OffsetY;
	override bool OnDrag(Widget w, int x, int y)
	{
		Trace("EditorDialog::OnDrag");
		if (w == WindowDragWrapper) {
			m_LayoutRoot.GetPos(m_OffsetX, m_OffsetY);
			m_OffsetX -= x; m_OffsetY -= y;		
			g_Game.GetUpdateQueue(CALL_CATEGORY_GUI).Insert(DragUpdate);	
		}
		
		return false;
	}
	
	override bool OnDragging(Widget w, int x, int y, Widget reciever) 
	{ 
		return true; 
	}
	
	private bool DragUpdate()
	{
		int x, y;
		GetMousePos(x, y);
		m_LayoutRoot.SetPos(x + m_OffsetX, y + m_OffsetY);
		return false;
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		Trace("EditorDialog::OnDrop");
		g_Game.GetUpdateQueue(CALL_CATEGORY_GUI).Remove(DragUpdate);
		
		if (w == WindowDragWrapper) {
			m_LayoutRoot.SetPos(x + m_OffsetX, y + m_OffsetY);
	    }		
		
		return false;
	}
	
	override typename GetControllerType() {
		return DialogBaseController;
	}	
		
	override string GetLayoutFile() {
		return "DayZEditor/gui/Layouts/dialogs/DialogBase.layout";
	}
}