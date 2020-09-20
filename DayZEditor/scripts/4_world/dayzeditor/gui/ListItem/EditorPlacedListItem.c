
class EditorPlacedListItem: EditorListItem
{
	protected ref EditorObject m_EditorObject;
	EditorObject GetData() { 
		return m_EditorObject; 
	}
	
	void SetEditorObject(EditorObject data) 
	{ 
		EditorLog.Trace("EditorPlacedListItem::SetEditorObject"); 
		m_EditorObject = data;
		
		GetListItemController().ListItemLabel = m_EditorObject.GetDisplayName();
		GetListItemController().NotifyPropertyChanged("ListItemLabel");
		
		GetListItemController().ListItemIcon = GetIconFromMod(m_EditorObject.GetData().ObjectMod);
		GetListItemController().NotifyPropertyChanged("ListItemIcon");
				
		m_EditorObject.OnObjectSelected.Insert(EditorObjectSelected);
		m_EditorObject.OnObjectDeselected.Insert(EditorObjectDeselected);	
	}
	
	
	void EditorObjectSelected(EditorObject data) {
		Select();
	}
	
	void EditorObjectDeselected(EditorObject data) {
		Deselect();
	}
	
	override void ListItemExecute(ButtonCommandArgs args)
	{
		switch (args.GetMouseButton()) {
			
			case 0: {
				if (KeyState(KeyCode.KC_LCONTROL)) {
					GetEditor().ToggleSelection(GetData());
				} else if (KeyState(KeyCode.KC_LSHIFT)) {
					
					
					bool started_select;
					
					for (int i = 0; i < ParentList.Count(); i++) {
						EditorListItem list_item = ParentList[i];			
						if (started_select) {
							
							if (list_item.IsSelected() || list_item == this) {
								break;
							}
							
							GetEditor().SelectObject(EditorPlacedListItem.Cast(list_item).GetData());
							
						} else if (!started_select && (list_item.IsSelected() || list_item == this)) {
							started_select = true;
							continue;
						}
						
						
					}
					
				} else {
					GetEditor().ClearSelection();
					GetEditor().SelectObject(GetData());
				}
				break;
			} 
			
			case 1: {
				EditorContextMenu context_menu = new EditorContextMenu();
				int x, y;
				GetMousePos(x, y);
				context_menu.SetPosition(x, y);
				break;
			}
		}
	}
	
	override void ListItemVisibleExecute(ButtonCommandArgs args)
	{
		switch (args.GetMouseButton()) {
			
			case 0: {
				m_EditorObject.ShowWorldObject(args.GetButtonState());
				break;
			}
			
		}
	}
	
		
	override bool OnDrag(Widget w, int x, int y)
	{
		EditorLog.Trace("EditorPlaceableListItem::OnDrag");	
		
		return true;
	}
	
	override bool OnDrop(Widget w, int x, int y, Widget reciever)
	{
		EditorLog.Trace("EditorPlaceableListItem::OnDrop");
		RecursiveGetParent(reciever, "EditorListItem");
		EditorListItem target_item = GetListItemFromWidget(reciever);
		if (!target_item) {
			return false;
		}
		
		switch (target_item.Type()) {
			
			case EditorPlacedListItem: {
				
				break;
			}
			
			case EditorCollapsibleListItem: {
				EditorCollapsibleListItem.Cast(target_item).AddListItem(this);
				break;
			}			
		}
		
		
		return true;
	}
}
