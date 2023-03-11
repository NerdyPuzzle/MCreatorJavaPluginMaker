package net.nerdypuzzle.wfsf;

public class Launcher extends JavaPlugin {

   public static final Logger LOG = LogManager.getLogger("wfsf");
   public Launcher(Plugin plugin) {
       super(plugin);
       addListener(PreGeneratorsLoadingEvent.class, event -> PluginElementTypes.load());
       LOG.info("Plugin was loaded");
   }
}