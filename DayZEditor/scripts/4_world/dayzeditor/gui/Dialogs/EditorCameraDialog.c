
static float DEFAULT_FOV = -1;
static float DEFAULT_NEARPLANE = -1;


class EditorCameraDialogControllerData
{
	static float DOFDistance;
	static float DOFBlur;
	static float Blur;
	static float Vignette;
	static float Sharpness;
}

class EditorCameraDialogController: Controller
{
	
	protected EditorCamera m_EditorCamera;
	
	float fov;
	float blur;
	float near_plane;
	
	float dof_distance;	
	float dof_blur;
	
	float vignette;
	float sharpness;
	
	void SetCamera(EditorCamera editor_camera)
	{
		EditorLog.Trace("EditorCameraDialogController");
		m_EditorCamera = editor_camera;
		
		fov = m_EditorCamera.GetCurrentFOV();
		near_plane = m_EditorCamera.GetNearPlane();
		
		blur = EditorCameraDialogControllerData.Blur;
		dof_distance = EditorCameraDialogControllerData.DOFDistance;
		dof_blur = EditorCameraDialogControllerData.DOFBlur;
		vignette = EditorCameraDialogControllerData.Vignette;
		sharpness = EditorCameraDialogControllerData.Sharpness;
	}
		
	
	override void PropertyChanged(string property_name)
	{
		switch (property_name) {
			
			case "fov": {
				m_EditorCamera.SetFOV(fov);
				break;
			}			
			
			case "near_plane": {
				m_EditorCamera.SetNearPlane(near_plane);
				break;
			}			
			
			case "dof_blur":
			case "dof_distance": {
				EditorCameraDialogControllerData.DOFDistance = dof_distance;
				EditorCameraDialogControllerData.DOFBlur = dof_blur;
				m_EditorCamera.SetFocus(dof_distance, dof_blur);
				break;
			}
			
			case "vignette": {
				EditorCameraDialogControllerData.Vignette = vignette;
				PPEffects.SetVignette(EditorCameraDialogControllerData.Vignette, 0, 0, 0);
				break;
			}
			
			case "blur": {
				EditorCameraDialogControllerData.Blur = blur;
				PPEffects.SetBlur(EditorCameraDialogControllerData.Blur);
				break;
			}
			
			case "sharpness": {
				
				EditorCameraDialogControllerData.Sharpness = sharpness;
				GetGame().GetWorld().GetMaterial("Graphics/Materials/postprocess/filmgrainNV").SetParam("Sharpness", EditorCameraDialogControllerData.Sharpness);
				break;
			}
		}		
	}
}



class EditorCameraDialog: EditorDialog
{
	protected EditorCamera m_EditorCamera;
	protected ref EditorCameraDialogController m_EditorCameraDialogController;
	
	void EditorCameraDialog(EditorCamera editor_camera)
	{
		EditorLog.Trace("EditorCameraDialog");
		m_EditorCamera = editor_camera;
	
		if (DEFAULT_FOV == -1) {
			DEFAULT_FOV = m_EditorCamera.GetCurrentFOV();
		}
		
		if (DEFAULT_NEARPLANE == -1) {
			DEFAULT_NEARPLANE = m_EditorCamera.GetNearPlane();
		}
		
		m_EditorCameraDialogController = new EditorCameraDialogController();
		m_EditorCameraDialogController.SetCamera(m_EditorCamera);
		
		EditorPrefabGroup camera_group = new EditorPrefabGroup("Camera");
		

		camera_group.AddPrefab(new EditorPrefabSlider("FOV", "fov", 0, 0, 2));
		camera_group.AddPrefab(new EditorPrefabSlider("Gaussian Blur", "blur", 0, 0, 1));
		camera_group.AddPrefab(new EditorPrefabSlider("Near Plane", "near_plane", 0, 0, 1));
		camera_group.AddPrefab(new EditorPrefabSlider("DOF Distance", "dof_distance", 0, 0, 1));
		camera_group.AddPrefab(new EditorPrefabSlider("DOF Blur", "dof_blur", 0, 0, 1));
		camera_group.AddPrefab(new EditorPrefabSlider("Vignette", "vignette", 0, 0, 1));
		camera_group.AddPrefab(new EditorPrefabSlider("Sharpness", "sharpness", 0, 0, 1));
		
		camera_group.SetController(m_EditorCameraDialogController);
		
		AddContent(camera_group);
		
		SetTitle("Camera Controller");
		
		AddButton("Default", "ResetDefault");
		AddButton("Close", "CloseDialog");
	}
	
	void ResetDefault()
	{
		EditorLog.Trace("EditorCameraDialog::ResetDefault");
		
		m_EditorCameraDialogController.fov = DEFAULT_FOV;
		m_EditorCameraDialogController.near_plane = DEFAULT_NEARPLANE;
		
		m_EditorCameraDialogController.dof_distance = 0;
		m_EditorCameraDialogController.dof_blur = 0;
		
		m_EditorCameraDialogController.NotifyPropertyChanged("fov");
		m_EditorCameraDialogController.NotifyPropertyChanged("near_plane");
		m_EditorCameraDialogController.NotifyPropertyChanged("dof_distance");
		m_EditorCameraDialogController.NotifyPropertyChanged("dof_blur");
		
		PPEffects.ResetAll();
	}
	
}

