
class EditorListItemController: Controller
{
	private EditorListItem m_ListItem;
	void SetListItem(EditorListItem list_item) {
		m_ListItem = list_item;		
	}
	
	string ListItemLabel;
	string ListItemIcon;
	
	ref EditorListItemSet ChildListItems;
	
	void EditorListItemController()	{
		EditorLog.Trace("EditorListItemController");
	}
	
	override void OnWidgetScriptInit(Widget w)
	{
		EditorLog.Trace("EditorListItemController::OnWidgetScriptInit");
		super.OnWidgetScriptInit(w);
		
		ChildListItems = new EditorListItemSet("ChildListItems", this);
	}

	void ListItemExecute(ButtonCommandArgs args) {
		m_ListItem.ListItemExecute(args);
	}
	
	void ListItemVisibleExecute(ButtonCommandArgs args) {
		m_ListItem.ListItemVisibleExecute(args);
	}
	
	void ListItemCollapseExecute(ButtonCommandArgs args) {
		m_ListItem.ListItemCollapseExecute(args);
	}
	
	// janky way to try to get the group head to select
	/*
	override bool OnEvent(EventType eventType, Widget target, int parameter0, int parameter1)
	{
		if (m_ListItem.Type() == EditorCollapsibleListItem && ChildListItems.Count() > 0) {
			if (AllChildrenSelected()) {
				m_ListItem.Select();
			} else {
				m_ListItem.Deselect();
			}
		}
		return super.OnEvent(eventType, target, parameter0, parameter1);
	}
*/
	
	private bool AllChildrenSelected()
	{
		for (int i = 0; i < ChildListItems.Count(); i++) {
			EditorListItem list_item = EditorListItem.Cast(ChildListItems[i]);
			if (!list_item.IsSelected()) {
				return false;
			}
		}
		
		return true;
	}
}

