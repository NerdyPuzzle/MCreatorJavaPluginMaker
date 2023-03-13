package net.nerdypuzzle.testttt.ui.modgui;

public class PluginElementGUI extends ModElementGUI<PluginElement> {
	private final JCheckBox testcheckbox = L10N.checkbox("elementgui.common.enable");
	private final VTextField testtextfield = new VTextField(6);
	private final JSpinner testnumberfield = new JSpinner(new SpinnerNumberModel(1.0, 1, 1, 0.100000));
	private final VComboBox<String> testtexture = new SearchableComboBox<>();
	private final Model testmodel_default = new Model.BuiltInModel("Default");
	private final SearchableComboBox<Model> testmodel = new SearchableComboBox<>(new Model[] { testmodel_default });
	private MCItemHolder testitem;
	private final JComboBox<String> testdropdown = new JComboBox<>(
		new String[] { "dhedhs", "wfuaf", "fkjahf", "wkha", "akw", "wkgkw", "akjhgwj", "akjhgk" });
	private final Model sege_default = new Model.BuiltInModel("Default");
	private final SearchableComboBox<Model> sege = new SearchableComboBox<>(new Model[] { sege_default });
	private final JComboBox<String> wfwg = new JComboBox<>(
		new String[] { "egdgs" });
	private final JTextField fwsdwg = new JTextField(3);
	private final JCheckBox wsfw = L10N.checkbox("elementgui.common.enable");
	private final JCheckBox wsdaws = L10N.checkbox("elementgui.common.enable");
	private final JCheckBox dwsfwg = L10N.checkbox("elementgui.common.enable");
	private final JCheckBox sdawf = new JCheckBox();
	private MCItemHolder wwg;
	private MCItemHolder sadawsgw;
	private MCItemHolder sfsa;
	private final JSpinner wsf = new JSpinner(new SpinnerNumberModel(1.0, 1, 1, 0.100000));
	private final JComboBox<String> ssgsedgs = new JComboBox<>(
		new String[] { "this", "is", "a", "test", "of", "my", "dropdown", "system" });
	private final JComboBox<String> fawgws = new JComboBox<>(
		new String[] { "I", "guess", "it", "works", "pretty", "well", "huh?" });
	private final JCheckBox fedgsg = L10N.checkbox("elementgui.common.enable");
	private final JSpinner dwgw = new JSpinner(new SpinnerNumberModel(1.0, -4, 6, 1.000000));
	private final Model wsfwsg_default = new Model.BuiltInModel("Default");
	private final SearchableComboBox<Model> wsfwsg = new SearchableComboBox<>(new Model[] { wsfwsg_default });
	private final JSpinner hdbed = new JSpinner(new SpinnerNumberModel(1.0, 2, 3, 0.400000));
	private MCItemHolder wsfwgws;
	private final JCheckBox wwsag = L10N.checkbox("elementgui.common.enable");
	private final VTextField dgbsdh = new VTextField(69);
	private final VComboBox<String> gawg = new SearchableComboBox<>();
	private final Model wt4eg_default = new Model.BuiltInModel("Default");
	private final SearchableComboBox<Model> wt4eg = new SearchableComboBox<>(new Model[] { wt4eg_default });

	private final ValidationGroup page1group = new ValidationGroup();
	private final ValidationGroup page2group = new ValidationGroup();
	private final ValidationGroup page3group = new ValidationGroup();

	public PluginElementGUI(MCreator mcreator, ModElement modElement, boolean editingMode) {
		super(mcreator, modElement, editingMode);
		this.initGUI();
		super.finalizeGUI();
	}

	@Override
	protected void initGUI() {
		testitem = new MCItemHolder(mcreator, ElementUtil::loadBlocks);
		wwg = new MCItemHolder(mcreator, ElementUtil::loadBlocksAndItems);
		sadawsgw = new MCItemHolder(mcreator, ElementUtil::loadBlocks);
		sfsa = new MCItemHolder(mcreator, ElementUtil::loadBlocksAndItems);
		wsfwgws = new MCItemHolder(mcreator, ElementUtil::loadBlocks);

		JPanel pane1 = new JPanel(new BorderLayout(10, 10));
		JPanel page1Panel = new JPanel(new GridLayout(22, 2, 10, 10));
		pane1.setOpaque(false);
		page1Panel.setOpaque(false);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gegseg"),
				L10N.label("elementgui.element.testcheckbox")));
		page1Panel.add(testcheckbox);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("edghegeg"),
				L10N.label("elementgui.element.testtextfield")));
		page1Panel.add(testtextfield);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("hedhedhgsedh"),
				L10N.label("elementgui.element.testnumberfield")));
		page1Panel.add(testnumberfield);

		page1Panel.add(new JEmptyBox()); page1Panel.add(new JEmptyBox());

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("sehedhs"),
				L10N.label("elementgui.element.testtexture")));
		page1Panel.add(testtexture);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("wgwg"),
				L10N.label("elementgui.element.testmodel")));
		page1Panel.add(testmodel);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("hehsedh"),
				L10N.label("elementgui.element.testitem")));
		page1Panel.add(testitem);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gedgeh"),
				L10N.label("elementgui.element.testdropdown")));
		page1Panel.add(testdropdown);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("edsdgs"),
				L10N.label("elementgui.element.sege")));
		page1Panel.add(sege);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gedgedg"),
				L10N.label("elementgui.element.wfwg")));
		page1Panel.add(wfwg);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gfwgwg"),
				L10N.label("elementgui.element.fwsdwg")));
		page1Panel.add(fwsdwg);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gawgawg"),
				L10N.label("elementgui.element.wsfw")));
		page1Panel.add(wsfw);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("fwac"),
				L10N.label("elementgui.element.wsdaws")));
		page1Panel.add(wsdaws);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gawga"),
				L10N.label("elementgui.element.dwsfwg")));
		page1Panel.add(dwsfwg);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gwgwg"),
				L10N.label("elementgui.element.sdawf")));
		page1Panel.add(sdawf);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("wsgwga"),
				L10N.label("elementgui.element.wwg")));
		page1Panel.add(wwg);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("sgawgwg"),
				L10N.label("elementgui.element.sadawsgw")));
		page1Panel.add(sadawsgw);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gdgedg"),
				L10N.label("elementgui.element.sfsa")));
		page1Panel.add(sfsa);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("wdwsfg"),
				L10N.label("elementgui.element.wsf")));
		page1Panel.add(wsf);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("sdhsdh"),
				L10N.label("elementgui.element.ssgsedgs")));
		page1Panel.add(ssgsedgs);

		page1Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("wgwg"),
				L10N.label("elementgui.element.fawgws")));
		page1Panel.add(fawgws);

		page1Panel.add(L10N.label("elementgui.element.fedgsg"));
		page1Panel.add(fedgsg);

		pane1.add("Center", PanelUtils.totalCenterInPanel(page1Panel));

		JPanel pane2 = new JPanel(new BorderLayout(10, 10));
		JPanel page2Panel = new JPanel(new GridLayout(7, 2, 10, 10));
		pane2.setOpaque(false);
		page2Panel.setOpaque(false);

		page2Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gwsgwga"),
				L10N.label("elementgui.element.dwgw")));
		page2Panel.add(dwgw);

		page2Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("wgw"),
				L10N.label("elementgui.element.wsfwsg")));
		page2Panel.add(wsfwsg);

		page2Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("edgdgedgeh"),
				L10N.label("elementgui.element.hdbed")));
		page2Panel.add(hdbed);

		page2Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("wgawgh"),
				L10N.label("elementgui.element.wsfwgws")));
		page2Panel.add(wsfwgws);

		page2Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("gwgwg"),
				L10N.label("elementgui.element.wwsag")));
		page2Panel.add(wwsag);

		page2Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("hdrhrfj"),
				L10N.label("elementgui.element.dgbsdh")));
		page2Panel.add(dgbsdh);

		page2Panel.add(HelpUtils.wrapWithHelpButton(this.withEntry("awhgsg"),
				L10N.label("elementgui.element.gawg")));
		page2Panel.add(gawg);

		pane2.add("Center", PanelUtils.totalCenterInPanel(page2Panel));

		JPanel pane3 = new JPanel(new BorderLayout(10, 10));
		JPanel page3Panel = new JPanel(new GridLayout(14, 2, 10, 10));
		pane3.setOpaque(false);
		page3Panel.setOpaque(false);

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(new JEmptyBox()); page3Panel.add(new JEmptyBox());

		page3Panel.add(L10N.label("elementgui.element.wt4eg"));
		page3Panel.add(wt4eg);

		pane3.add("Center", PanelUtils.totalCenterInPanel(page3Panel));

		testcheckbox.setOpaque(false);
		wsfw.setOpaque(false);
		wsdaws.setOpaque(false);
		dwsfwg.setOpaque(false);
		sdawf.setOpaque(false);
		fedgsg.setOpaque(false);
		wwsag.setOpaque(false);

		page1group.addValidationElement(testtextfield);
		page1group.addValidationElement(testtexture);
		page1group.addValidationElement(testmodel);
		page1group.addValidationElement(sege);
		page2group.addValidationElement(wsfwsg);
		page2group.addValidationElement(dgbsdh);
		page2group.addValidationElement(gawg);
		page3group.addValidationElement(wt4eg);

		if (!isInEditingMode) {
			testtextfield.setText(StringUtils.machineToReadableName(modElement.getName()));
		}
		if (!isInEditingMode) {
			dgbsdh.setText(StringUtils.machineToReadableName(modElement.getName()));
		}

		addPage(L10N.t("elementgui.element.page1"), pane1);
		addPage(L10N.t("elementgui.element.page2"), pane2);
		addPage(L10N.t("elementgui.element.page3"), pane3);
	}

	@Override
	protected AggregatedValidationResult validatePage(int page) {
		if (page == 0)
			return new AggregatedValidationResult(page1group);
		if (page == 1)
			return new AggregatedValidationResult(page2group);
		if (page == 2)
			return new AggregatedValidationResult(page3group);
	}

