package net.nerdypuzzle.bestawesome;

public class Launcher extends JavaPlugin {

   public static final Logger LOG = LogManager.getLogger("bestawesome");
   public Launcher(Plugin plugin) {
       super(plugin);
       addListener(PreGeneratorsLoadingEvent.class, event -> PluginElementTypes.load());
       LOG.info("Plugin was loaded");
   }
}