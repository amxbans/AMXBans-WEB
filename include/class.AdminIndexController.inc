<?php


class AdminIndexController
{
    private $site;
    private $method;
    protected $config;

    /**
     * AdminController constructor.
     *
     * @param Site   $config
     * @param string $method
     * @param string $site
     *
     * @throws Exception
     */
    public function __construct (Site $config, string $method, string $site) {
        $this->config = $config;
        $this->method = $method;
        $this->site = $site;

        // If there's any extra action needed, it has to be placed here for all the 'admin' sites

        ////////////

        $site = $method . ucfirst($site);
        if (method_exists($this, $site))
            $this->$site();
        else
            throw new Exception('Site "' . $site . '" not found');
    }

    private function index ()
    {
        if ($this->method !== 'get')
            $this->navigateTo();
    }

    private function navigateTo ($class)
    {

    }
}