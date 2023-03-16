package net.nerdypuzzle.testingplugin.element.types;

public class PluginElementTypes {
	public static ModElementType<?> PLUGINELEMENT;

	public static void load() {
		PLUGINELEMENT = register(
			new ModElementType<>("pluginelement", (Character) null, BaseType.OTHER, PluginElementGUI::new, PluginElement.class)
		);
	}
}