package net.nerdypuzzle.testingplugin;

public class Launcher extends JavaPlugin {

   public static final Logger LOG = LogManager.getLogger("Testing Plugin");
   public Launcher(Plugin plugin) {
       super(plugin);
       addListener(PreGeneratorsLoadingEvent.class, event -> PluginElementTypes.load());
       LOG.info("Plugin was loaded");
   }
}