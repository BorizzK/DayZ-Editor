class EditorSettings 
{
	// shit thats gotta be changed
	static float VIEW_DISTANCE = 12000;
	static float OBJECT_VIEW_DISTANCE = 5000;
	
	static bool MAGNET_PLACEMENT = false;
	static bool MAINTAIN_HEIGHT = false;
	static bool SNAPPING_MODE = false;
	static bool COLLIDE_ON_DRAG = false;
	
	// Autosave timer in SECONDS!!!!!!!!!!!!!!!!
	static int AUTOSAVE_TIMER = 240;

	
	void EditorSettings()
	{
		Print("EditorSettings");
	}
	
	
	
	
	static void Load()
	{
		GetGame().GetWorld().SetViewDistance(VIEW_DISTANCE);
		GetGame().GetWorld().SetObjectViewDistance(OBJECT_VIEW_DISTANCE);
		
		// todo load em from ini file
	}
	
	
	static void Save()
	{
		// todo save settings to ini or something
	}

	
	// private members
	private PlaceableObjectCategory m_PlaceableObjectCategory;
	PlaceableObjectCategory GetPlaceableObjectCategory() { return m_PlaceableObjectCategory; }
	
	void SetPlaceableObjectCategory(PlaceableObjectCategory category) 
	{ 
		m_PlaceableObjectCategory = category;
		EditorEvents.PlaceableCategoryChangedInvoke(this, category);
	}
	
}