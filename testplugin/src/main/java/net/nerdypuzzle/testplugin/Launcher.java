package net.nerdypuzzle.testplugin;

public class Launcher extends JavaPlugin {

   public static final Logger LOG = LogManager.getLogger("testplugin");
   public Launcher(Plugin plugin) {
       super(plugin);
       addListener(PreGeneratorsLoadingEvent.class, event -> PluginElementTypes.load());
       LOG.info("Plugin was loaded");
   }
}