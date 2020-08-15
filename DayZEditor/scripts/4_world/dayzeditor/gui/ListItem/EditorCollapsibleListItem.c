// temp
static int groupcount = 0;
class EditorCollapsibleListItem: EditorListItem
{
	

	private ref array<ref EditorListItem> m_CategoryChildren;
	ref array<ref EditorListItem> GetChildren() { return m_CategoryChildren; }
	
	void EditorCollapsibleListItem() 
	{ 
		Print("EditorCollapsibleListItem");
		m_CategoryChildren = new array<ref EditorListItem>();
		
		SetText(string.Format("group%1", groupcount));
		groupcount++;
		
		EditorEvents.OnObjectDeselected.Insert(ObjectDeselected); 
	}
	
	

	void RemoveListItem(EditorListItem item)
	{
		int index = m_CategoryChildren.Find(item);
		if (index == -1) return;
		m_CategoryChildren.Remove(index);
	}
	
	bool ContainsChildListItem(EditorListItem item)
	{
		foreach (EditorListItem child: m_CategoryChildren) {
			
			// Check if child is collapsible
			EditorCollapsibleListItem collapsible;
			if (CastTo(collapsible, child)) {
				return collapsible.ContainsChildListItem(item);
			} 
			else if (child == item) {
				return true;
			}
		}
		
		return false;
	}
	
	override void SetNestIndex(int index)
	{
		super.SetNestIndex(index);
		foreach (EditorListItem item: m_CategoryChildren) {
			item.SetNestIndex(index + 1);
		}
	}
	
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		Print("EditorCollapsibleListItem::OnClick");
	
		if (button == 0) {
			
			switch (w) {

				case m_ListItemButton: {
					Select();
					SelectAllChildren(m_CategoryChildren);					
					break;
				}
			}			
		}
		
		return super.OnClick(w, x, y, button);
	}
	
	
	override bool OnListItemDropReceived(EditorListItem target)
	{
		Print("EditorCollapsibleListItem::OnListItemDropReceived");
				
		target.SetNestIndex(GetNestIndex() + 1);
		m_CategoryChildren.Insert(target);
		m_ListItemChildren.AddChild(target.GetRoot());	
		
		return true;
	}
	
	override bool OnListItemDrop(EditorListItem target)
	{
		Print("EditorCollapsibleListItem::OnListItemDrop");
		
		if (ContainsChildListItem(target)) {
			return false;
		}
		return true;
	}
	
	void ObjectDeselected(Class context, EditorObject target)
	{
		Deselect();
	}
	
	void SelectAllChildren(ref array<ref EditorListItem> children)
	{
		foreach (EditorListItem list_item: children) {
			EditorPlacedListItem placed_item;
			EditorCollapsibleListItem collapsible_item;
			if (CastTo(placed_item, list_item)) {
				GetEditor().SelectObject(placed_item.GetData());
			} else if (CastTo(collapsible_item, list_item)) {
				collapsible_item.Select();
				SelectAllChildren(collapsible_item.GetChildren());
			}
		}
	}
	
}